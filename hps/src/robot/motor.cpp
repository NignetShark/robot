
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "hps_0.h"
#include "hps_base.h"
#include "robot/motor.hpp"



Motor::Motor(int* status) {
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if(fd < 0) {
        *status = 1; // Can't open memory
        return;
    }

    base = mmap(NULL, REG_SPAN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, REG_BASE);
    if(base == MAP_FAILED)
    {
        *status = 2; // Can't map memory
        close(fd);
        return;
    }

    motor_left = (int32_t volatile*)(base + MOTOR_LEFT_BASE);
    motor_right = (int32_t volatile*)(base + MOTOR_RIGHT_BASE);

    *status = 0;
}


Motor::~Motor() {
    *motor_left=0;
    *motor_right=0;
    munmap(base, REG_SPAN);
    close(fd);   
}


void Motor::setCmd(int left, int right) {
    *motor_left = abs(left) | ((left >= 0) << 8);
    *motor_right = abs(right) | ((right >= 0) << 8);
}