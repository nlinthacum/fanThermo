#include <IRremote.h>


IRsend irsend;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  int khz = 38;// 38kHz carrier frequency for the NEC protocol
  unsigned int On[] ={1250,400, 1250,400, 450,1250, 1250,400, 1250,400, 450,1250, 400,1250, 450,1200, 450,1250, 400,1250, 450,1200, 1300};  // Power 
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);

  delay(300);
  }
