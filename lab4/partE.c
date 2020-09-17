#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
int a=open("/dev/memory",O_RDWR);
ioctl(a,(argv[1] != '0'),0);
}