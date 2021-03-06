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
static int32_t volatile *motor_left;
static int32_t volatile *motor_right;
static int fd;

void signal_handler(int signo)
{
    *motor_left=0;
    *motor_right=0;
    munmap(base, REG_SPAN);
    close(fd);
    exit(0);
}


int main(int argc, char **argv) {
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

    motor_left = (int32_t volatile*)(base + MOTOR_LEFT_BASE);
    motor_right = (int32_t volatile*)(base + MOTOR_RIGHT_BASE);
    signal(SIGINT, signal_handler);

    int left, right;

    if(argc == 3) {
        left = atoi(argv[1]);
        right = atoi(argv[2]);
    } else {
        left = 0;
        right = 0;
        printf("Wrong arguments.\n");
    }

    *motor_left = abs(left) | ((left >= 0) << 8);
    *motor_right = abs(right) | ((right >= 0) << 8);
    
    printf("Motor left set to %i and right to %i.\n", left, right);

    /*
    while(1)
    {
        usleep(250000);
        printf("Sonar value is : %d\n", *motor_left);
    }*/

    return 0;
}
