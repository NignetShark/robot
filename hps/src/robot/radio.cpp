#include <unistd.h>

#include "robot/radio.hpp"

#define POLL_DELAY_MS 10

#define NB_CHANNEL 125
#define WRITING_PIPE_ADDRESS 0xF0F0F0F0D2LL
#define READING_PIPE_ADDRESS 0xF0F0F0F0E1LL

/****************************************************************************/

int Radio::test_strength() {
    return radio->testRPD();
}

/****************************************************************************/

int Radio::check_failure() {
    return radio->failureDetected;
}

/****************************************************************************/

int Radio::is_connected() {
    return radio->isChipConnected();
}

/****************************************************************************/

void Radio::print_settings() {
    radio->printDetails();
}

/****************************************************************************/

void Radio::setup() { 
    radio->enableDynamicPayloads();
    radio->setDataRate(RF24_250KBPS);
    radio->setRetries(5, 15);
    radio->setPALevel(RF24_PA_MAX, 1);
    
    radio->openWritingPipe(WRITING_PIPE_ADDRESS);
    radio->openReadingPipe(1, READING_PIPE_ADDRESS);
    radio->startListening();
}

/****************************************************************************/

void Radio::reset() {
    radio->begin();
    radio->failureDetected = 0;
    setup();
}

/****************************************************************************/

int Radio::scan_for_interference() {
    uint8_t saved_channel = radio->getChannel();
    uint8_t channels[NB_CHANNEL];

    radio->startListening();

    for(uint8_t channel = 0; channel < NB_CHANNEL; channel++) {
        printf("Scan frequencies %d MHz", 2400 + channel);
        radio->setChannel(channel);
        delay(10);
        channels[channel] = radio->testRPD();
        fflush(stdout);
        printf("\33[2K\r");
    }

    printf("\n");
    for(uint8_t channel = 0; channel < NB_CHANNEL; channel++) {
        if(channels[channel] == 1) {
            printf("Channel %d MHz busy\n", 2400 + channel, radio->testRPD());
        }
    }

    radio->setChannel(saved_channel);
    return channels[saved_channel];
}

/****************************************************************************/

int Radio::wait_for_message(int max_delay_ms) {
    unsigned int delay = 0;
    radio->startListening();
    while (!radio->available()) {
        if(delay >= max_delay_ms) return -1;
        usleep(POLL_DELAY_MS * 1000);
        delay += POLL_DELAY_MS;
    }
    nb_packet_received += 1;
    return 0;
}

/****************************************************************************/

char* Radio::listen_dyn(int* size, int max_delay_ms) {
    if(wait_for_message(max_delay_ms) < 0) return NULL;

    uint8_t len = radio->getDynamicPayloadSize();
    char* payload = (char *)malloc(len * sizeof(char));

    radio->read(payload, len);
    payload[len] = 0;

    if(size != NULL) *size = len;

    return payload;   
}

/****************************************************************************/

int Radio::listen(char* message, int max_delay_ms) {
    if(wait_for_message(max_delay_ms) < 0) return 0;

    uint8_t len = radio->getDynamicPayloadSize();

    radio->read(message, len);
    message[len] = 0;

    return len;
}

/****************************************************************************/

void Radio::send(char* message, int length) {
    radio->stopListening();
    radio->write(message, length);
    radio->startListening();
}

/****************************************************************************/

Radio::Radio(int cs_pin) {
    nb_packet_received = 0;
    radio = new RF24(cs_pin, 0);
    radio->begin();
    setup();
}

/****************************************************************************/

Radio::~Radio() {
    delete radio;
}

/****************************************************************************/