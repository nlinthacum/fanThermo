#include<Wire.h>

#define SLAVE_ADDR 9

#define ANSWERSIZE 1
int buttonPin = 7;
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  

}

void loop() {
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  delay(50);

  // put your main code here, to run repeatedly:
  //Send data
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(buttonState);
  Wire.endTransmission();

  //Recieve Data
  //Wire.requestFrom(SLAVE_ADDR, ANSWERSIZE);
  //String response = "";
  //while (Wire.available()) {
   // char ch = Wire.read();
    //response += ch; 
  //}
  //Serial.println(response);

  
  
}
