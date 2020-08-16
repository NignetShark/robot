#ifndef __MOTOR_H__
#define __MOTOR_H__

class Motor {
    public:
    Motor(int* status);
    ~Motor();
    void setCmd(int left, int right);

    private:
    int fd;     // File descriptor used to open /dev/mem
    void *base; // mmap base
    int32_t volatile *motor_left;
    int32_t volatile *motor_right;
};

#endif
