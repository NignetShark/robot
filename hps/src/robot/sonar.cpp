#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "hps_0.h"
#include "hps_base.h"

#include "robot/sonar.hpp"

#define CONV_MM (0.3463 / 100)

Sonar::Sonar(int* status)
{
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
    
    sonar0 = (int32_t volatile*)(base + SONAR_0_BASE);
    sonar1 = (int32_t volatile*)(base + SONAR_1_BASE);
}

Sonar::~Sonar()
{
    munmap(base, REG_SPAN);
    close(fd);   
}

void Sonar::read(sonar_data* data, int32_t volatile* sonar) {
    int32_t value = *sonar;
    if(value >= NO_ERROR) {
        data->distance = value * CONV_MM;
        data->error_code = NO_ERROR;   
    } else {
        data->distance = 0;
        data->error_code = (sonar_code_t)value;  
    }
}

void Sonar::read() {
    read(&values[0], sonar0);
    read(&values[1], sonar1);
}