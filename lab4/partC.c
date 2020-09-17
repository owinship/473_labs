#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>	/* O_ACCMODE */
//#include <linux/system.h>		/* cli(), *_flags */
#include <linux/uaccess.h>	/* copy_from/to_user */

MODULE_LICENSE ("Dual BSD/GPL");

int memory_open (struct inode *inode, struct file *filp);
int memory_release (struct inode *inode, struct file *filp);
ssize_t memory_read (struct file *filp, char *buf, size_t count,
		     loff_t * f_pos);
ssize_t memory_write (struct file *filp, const char *buf, size_t count,
		      loff_t * f_pos);
void memory_exit (void);
int memory_init (void);

void add_to_FIFO(char *fifo, size_t size, char toadd){
	size_t i = size-1;
	for(i = size-1; i > 0; i= i-1){
		fifo[i] = fifo[i-1];
	}
	fifo[0] = toadd;
}

struct file_operations memory_fops = 
{
  .read = memory_read,
  .write = memory_write,
  .open = memory_open,
  .release = memory_release
};

module_init (memory_init);
module_exit (memory_exit);

int memory_major = 60;
char *memory_buffer;

int
memory_init (void)
{
  int result;
  result = register_chrdev (memory_major, "memory", &memory_fops);
  if (result < 0)
    {
      printk ("<1>memory: cannot obtain major number %d\n", memory_major);
      return result;
    }

  /* Allocating memory for the buffer */
  memory_buffer = kmalloc (6, GFP_KERNEL);
  if (!memory_buffer)
    {
      result = -ENOMEM;
      goto fail;
    }

  memset (memory_buffer, 0,6);
  memory_buffer[5] = '\0';
  printk ("<1> Inserting memory module\n");
  return 0;

fail:
  memory_exit ();
  return result;
}

void
memory_exit (void)
{
  unregister_chrdev (memory_major, "memory");
  if (memory_buffer)
    {
      kfree (memory_buffer);
    }
  printk ("<1>Removing memory module\n");
}

int
memory_open (struct inode *inode, struct file *filp)
{
  return 0;
}

int
memory_release (struct inode *inode, struct file *filp)
{
  return 0;
}

ssize_t
memory_read (struct file * filp, char *buf, size_t count, loff_t * f_pos)
{
  /* Transfering data to user space */
  /* Changing reading position as best suits */
  if (*f_pos < 5)
    {
      copy_to_user (buf, memory_buffer + *f_pos, 1);
      *f_pos += 1;
      return 1;
    }
  else
    {
      return 0;
    }
}

ssize_t
memory_write (struct file * filp, const char *buf, size_t count, loff_t * f_pos)
{
  char *tmp;
  tmp = buf;
  copy_from_user (memory_buffer, tmp, 1);
  add_to_FIFO(memory_buffer, 5, *tmp);
  *f_pos += 1;
  printk(memory_buffer);
  return 1;
}


