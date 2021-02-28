#include <Wire.h>

#define SLAVE_ADDR 9
#define ANSWERSIZE 1

//String answer = "Hello";

void requestEvent();
void receiveEvent();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDR); //only pass in when using the slave unit

  //Wire.onRequest(requestEvent);

  Wire.onReceive(receiveEvent);

}


/*
void requestEvent() {
  byte response[ANSWERSIZE];

  for (byte i = 0; i <ANSWERSIZE; i++) {
   response[i] = (byte)answer.charAt(i);
  }
  Wire.write(response, sizeof(response));
}
 */



void receiveEvent() {
  while (0 < Wire.available()) {
    byte x = Wire.read();
    Serial.println(x);
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  delay(50); 
}
