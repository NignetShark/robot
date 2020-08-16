#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "robot/robot.hpp"

#define CONSOLE_MOTOR_HEADER 'm'


int parse_int(void* ptr, int offset) {
    int* intptr = (int*)ptr; 
    intptr += offset;
    return *intptr;
}

int motor_parse(char* message, int size) {
    int left, right;
    if(sscanf(message, "m: %d %d\n", &left, &right) <= 0) {
        return -1;
    };
    printf("Left %d / Right %d\n", left, right);
    motor->setCmd(left, right);
    return 0;
}

int parse_cmd(char* message, int size) {
    switch(message[0]) {
        case CONSOLE_MOTOR_HEADER:
            return motor_parse(message, size);
        default:
            return -1;
    } 
}

#endif