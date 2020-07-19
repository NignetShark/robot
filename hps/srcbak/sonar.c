#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include "hps_0.h"

#define REG_BASE 0xff200000 // LW H2F Bridge Base Address
#define REG_SPAN 0x00200000 // LW H2F Bridge Span

static void *base;
static int32_t volatile *sonar;
static int fd;

void signal_handler(int signo)
{
    *sonar=0;
    munmap(base, REG_SPAN);
    close(fd);
    exit(0);
}


int main() {
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if(fd < 0)
    {
        printf("Can't open memory.\n");
        return -1;
    }

    base = mmap(NULL, REG_SPAN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, REG_BASE);
    if(base == MAP_FAILED)
    {
        printf("Can't map memory.\n");
        close(fd);
        return -1;
    }

    sonar = (int32_t volatile*)(base + FPGA_PIO_BASE);
    signal(SIGINT, signal_handler);

    while(1)
    {
        usleep(250000);
        printf("Sonar value is : %d\n", *sonar);
    }

    return 0;
}
