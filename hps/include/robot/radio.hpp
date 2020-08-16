#ifndef __RADIO_H__
#define __RADIO_H__

#include "RF24/RF24.h"

class Radio {
    public:
    unsigned int nb_packet_received;

    Radio(int cs_pin);
    ~Radio();

    int is_connected();
    void print_settings();
    int check_failure();
    int test_strength();
    int scan_for_interference();
    void setup();
    void reset();
    


    char* listen_dyn(int* size, int max_delay_ms);
    int listen(char* message, int max_delay_ms);
    void send(char* message, int length);

    private:
    int wait_for_message(int max_delay_ms);


    RF24* radio;
    int poll_delay;
    int max_payload_size;
    

};

#endif