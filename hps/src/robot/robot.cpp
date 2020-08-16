#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "robot/printing.hpp"
#include "robot/console.hpp"
#include "robot/robot.hpp"

#define CE_GPIO 2017
#define MAX_PAYLOAD_SIZE 255
#define TIMEOUT_RF_MS 1000

/**
 * Sequence for shuting down the robot
 */
void shutdown() {
    printf(BLU "\n> SHUTDOWN PROCEDURE..." RSTN);
    motor->setCmd(0, 0); // Stop motor.
    delete motor;
    delete radio;
    delete sonar;
}

/**
 * When SIGINT occurs
 **/
void signal_handler(int signo)
{
    shutdown();
    exit(0);
}

/**
 * Sequence for initializing the robot
 **/
int initialize() {
    int status;

    printf(BLU "[...] Starting initialization" RSTN);
    signal(SIGINT, signal_handler);

    // ===== Check FPGA status =====
    FILE *fp = popen("/usr/bin/FPGA-status -d", "r");
    if (fp == NULL) {
        printf(RED "[ERR] Failed to get FPGA status" RSTN);
        return -1;
    }

    if(fgetc(fp) - 48 != 4) {
        printf(RED "[ERR] FPGA may not be initialized. Check FPGA-status." RSTN);
        pclose(fp);
        return -1;
    }

    pclose(fp);
    
    // ===== Instantiate components =====
    // Instanciate motor
    motor = new Motor(&status);
    if(status != 0) {
        printf(RED "[ERR] Fail to bind motors (status = %d)" RSTN, status);
        return -1;
    }

    // Instanciate radio
    radio = new Radio(CE_GPIO);


    // Instanciate sonar
    sonar = new Sonar(&status);
    if(status != 0) {
        printf(RED "[ERR] Fail to bind motors (status = %d)" RSTN, status);
        return -1;
    }

    // ===== Check procedure =====
    printf(BLU "[...] Checking components" RSTN);

    // Detect if the NRF24L01 is connected.
    if(radio->is_connected() == 0) {
        printf(RED "[ERR] Radio is not connected." RSTN, status);
        return -1;
    }

    // Check for potential interference.
    if(radio->scan_for_interference() != 0) {
        printf(YEL "[WRN] Potential interference detected (maybe the base station is transmitting during the scan ?)" RSTN, status);
    }

    printf(GRN "[OK ] Initialization done." RSTN);
}


void no_rf_signal_emergency() {
    printf(YEL "[WRN] No RF signal." RSTN);
    motor->setCmd(0, 0); // Stop motors
}

/**
 * Wait for RF command
 **/
void wait_cmd(char* payload) {
    int size = radio->listen(payload, TIMEOUT_RF_MS);

    if(size == 0) {
        no_rf_signal_emergency();
        return;
    }

    if(parse_cmd(payload, size) < 0) {
        printf(YEL "[WRN] Unknown command : %s" RSTN, payload);
    }
}

void telemetry_report() {
    char payload[MAX_PAYLOAD_SIZE + 1];
    sprintf(payload, "r: %d\n", radio->nb_packet_received);
    radio->send(payload, strlen(payload));
}

int main(int argc, char** argv)
{
    if(initialize() < 0) exit(-1); 

    char payload[MAX_PAYLOAD_SIZE + 1];
    
    while (true)
    {
        //wait_cmd(payload);
        //telemetry_report();
        sonar->read();
        printf("Sonar 0 : %f [%d] \t Sonar 1 : %f [%d]\n", sonar->values[0].distance, sonar->values[0].error_code, sonar->values[1].distance, sonar->values[1].error_code);
        
        /*
        if(radio->check_failure()) {
            printf(MAG "[FLR] Radio failure detected. Reset connection." RSTN);
            radio->reset();
        }
        if(radio->test_strength()) {
            printf(BLU "[NOT] Radio failure detected. Reset connection." RSTN);
        }*/

        usleep(1000 * 100);
    }
    

    shutdown();
    return 0;
}





