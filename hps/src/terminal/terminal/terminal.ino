#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#define MAX_PAYLOAD_SIZE 32

RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

char payload[MAX_PAYLOAD_SIZE + 1]; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  printf_begin();

  radio.begin();

  // Enable dynamic payloads
  radio.enableDynamicPayloads();

  // Optionally, increase the delay between retries & # of retries
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(5, 15);
  radio.setPALevel(RF24_PA_MAX);
  
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);

  radio.printDetails();

  radio.stopListening();
  radio.write("m: 0 0\n", 7);
}

int listen_serial() {
  int index = 0;
  for(index = 0; index < MAX_PAYLOAD_SIZE; index++) {
    while(Serial.available() <= 0) ;
    char c = Serial.read();
    if(c == 10) {
      break;
    }
    payload[index] = c;
  }
  payload[index] = 0;
  return index;
}

void send_cmd(int len) {
  radio.write(payload, len);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int len = listen_serial();
  send_cmd(len);

  //Serial.print("Send > ");
  //Serial.println(payload);
}
