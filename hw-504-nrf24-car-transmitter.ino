#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

const int xAxisPin = A0; // Analog input pin for X-axis
const int yAxisPin = A1; // Analog input pin for Y-axis

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  int xPosition = analogRead(xAxisPin);
  int yPosition = analogRead(yAxisPin);

  char command = 'S';  // default = stop

  if (xPosition > 600) {
    command = 'F';
  }
  else if (xPosition < 400) {
    command = 'B';
  }
  else if (yPosition > 600) {
    command = 'R';
  }
  else if (yPosition < 400) {
    command = 'L';
  }
  
  radio.write(&command, sizeof(command));

  delay(20);  // prevents radio flooding

  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Command: ");
  Serial.print(command);
  Serial.println("");



}







