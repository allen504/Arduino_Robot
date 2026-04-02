#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(2, INPUT_PULLUP); // forward
  pinMode(3, INPUT_PULLUP); // backward
  pinMode(4, INPUT_PULLUP); // right
  pinMode(5, INPUT_PULLUP); // left
}

void loop() {

  char command = 'S';  // default = stop

  if (digitalRead(2) == LOW) {
    command = 'F';
  }
  else if (digitalRead(3) == LOW) {
    command = 'B';
  }
  else if (digitalRead(4) == LOW) {
    command = 'R';
  }
  else if (digitalRead(5) == LOW) {
    command = 'L';
  }

  radio.write(&command, sizeof(command));

  delay(20);  // prevents radio flooding
}

