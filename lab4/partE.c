#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
int a=open("/dev/memory",O_RDWR);
int pol = argv[1][0] != "0";
printf("pol %d %s\n",pol,argv[1]);
ioctl(a,(pol),0);
}