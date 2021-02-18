
#include <IRremote.h>
//#include <IRLibAll.h>

int thermPin = A1;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int IRledpin = 3;
int irCode = 273748619;


IRsend sender;

int IRreceiverPin = 6;
IRrecv irrecv(IRreceiverPin);
decode_results results;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(thermPin, INPUT);
   irrecv.enableIRIn();
   irrecv.blink13(true);

 pinMode(IRledpin, OUTPUT);
 pinMode(7, OUTPUT);
 digitalWrite(7, HIGH); 
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
 
if (irrecv.decode(&results)){
  Serial.println(results.value, HEX);
  irrecv.resume();
}

  
 //digitalWrite(IRledpin, HIGH);
 //   sender.sendRC5(irCode, 32);
  //delay(100);
if (Serial.read() != -1) {
  for (int i = 0; i < 3; i++)
  {
    sender.sendSony(0xa90, 12);
   delay(40);
  }
}
  
 

 
  /*
   switch (results.decode_type){
            case NEC: Serial.println("NEC"); break ;
            case SONY: Serial.println("SONY"); break ;
            case RC5: Serial.println("RC5"); break ;
            case RC6: Serial.println("RC6"); break ;
            case DISH: Serial.println("DISH"); break ;
            case SHARP: Serial.println("SHARP"); break ;
            case JVC: Serial.println("JVC"); break ;
            case SANYO: Serial.println("SANYO"); break ;
         //   case MITSUBISHI: Serial.println("MITSUBISHI"); break ;
            case SAMSUNG: Serial.println("SAMSUNG"); break ;
            case LG: Serial.println("LG"); break ;
            case WHYNTER: Serial.println("WHYNTER"); break ;
       //     case AIWA_RC_T501: Serial.println("AIWA_RC_T501"); break ;
            case PANASONIC: Serial.println("PANASONIC"); break ;
            case DENON: Serial.println("DENON"); break ;
          default:
            case UNKNOWN: Serial.println("UNKNOWN"); break ;
          }
        irrecv.resume();
}
*/

/*
  
  Vo = analogRead(thermPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" F"); 

  */



  

  
}
