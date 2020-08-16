#ifndef __SONAR__
#define __SONAR__

#include "hps_0.h"


typedef enum sonar_code {
    OBJECT_TOO_FAR,
    ERROR_TIMEOUT_ECHO_LOW,
    ERROR_ECHO_HIGH_DURING_TRIGGER,
    NO_ERROR
} sonar_code_t;

typedef struct sonar_data 
{
    float distance;
    sonar_code_t error_code;
} sonar_data_t;


class Sonar
{
public:
    Sonar(int* status);
    ~Sonar();
    void read();

    sonar_data_t values[2];

private:
    int fd;     // File descriptor used to open /dev/mem
    void *base; // mmap base
    int32_t volatile *sonar0;
    int32_t volatile *sonar1;

    void read(sonar_data* data, int32_t volatile * sonar);
    

};




#endif