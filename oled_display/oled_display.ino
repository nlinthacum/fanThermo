#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <IRremote.h>



#include <DS3232RTC.h>      // https://github.com/JChristensen/DS3232RTC
DS3232RTC myRTC;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET 4

 #define SCREEN_ADDRESS 0x3C 
 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);




#define  button1 8 //down temp; button states will be inverted since using internal pull-up resistor
#define  button2 9 //up temp

#define IR_SEND_PIN A5


IRsend irsend;

//irsend.enableIROut(A5);


  int button1State;
  int button2State;
  float desiredTemp;
  float currentTemp;
  int mode = 1; //for which cooling mode
   
void setup(){
 
  Serial.begin(9600);
  Wire.begin();
 

  pinMode(button1, INPUT);
  digitalWrite(button1, HIGH);

  pinMode(button2, INPUT);
  digitalWrite(button2, HIGH);


  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  myRTC.begin();



  display.display();
  delay(2000); // Pause for 2 seconds

    


  // Clear the buffer
  display.clearDisplay();



  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

     

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  display.clearDisplay();
  delay(2000);

  displayMode(mode);
 


  
 
}


  
void loop() {
   
displayRTC();



   
 
  if (mode == 1)
  {
    button1State = digitalRead(button1);
    button2State = digitalRead(button2);
 
 
    while (button2State != 0) 
    {
      
       
      
      button1State = digitalRead(button1);
      button2State = digitalRead(button2);
      if (button1State == 0) {
      switch (mode)
      {
        case 1: mode = 2;
                break;
        case 2: mode = 3;
                break;
        case 3: mode = 1;
                break;
      }
      }

      displayMode(mode);
      delay(150);

     
    }
  }


  Serial.print("Mode: ");
  Serial.println(mode);

 
  displayMode(mode);




  setTemp(mode);

 

 displayDesiredTemp();




  
  display.display();

  




 //decideToggle(desiredTemp, currentTemp, mode);  

   



  
}




void decideToggle(float desiredTemp, float currentTemp, int mode)
{
  if (((currentTemp - desiredTemp) > 1) && (mode == 2)) {
    sendIR(); //turn on
    Serial.println("Turning on");
   // displayMode(3);
    display.display();
  }

  
  if ((currentTemp - desiredTemp) >= -0.5) {
    sendIR();
    displayMode(1);
  }
}



void sendIR()
{
   int khz = 38;// 38kHz carrier frequency for the NEC protocol
   unsigned int On[] ={1250,400, 1250,400, 450,1250, 1250,400, 1250,400, 450,1250, 400,1250, 450,1200, 450,1250, 400,1250, 450,1200, 1300};  // Power 
   
   for (int i = 0; i < 16; i++)
   {
     irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   }
 
}

void displayMode(int mode)
{
    display.setTextSize(1);
    display.setCursor(0, 55);

    switch(mode) {
        case 1:
          display.setTextColor(BLACK, WHITE);
          display.print("off");
          display.setTextColor(WHITE, BLACK);
          display.print("    ");
          display.print("set");
          display.print("    ");
          display.print("cooling");
          break;

        case 2:
          display.setTextColor(WHITE, BLACK);
          display.print("off");
          display.print("    ");
          display.setTextColor(BLACK, WHITE);
          display.print("set");
          display.setTextColor(WHITE, BLACK);
          display.print("    ");
          display.print("cooling");
          break;

      case 3:
          display.setTextColor(WHITE, BLACK);
          display.print("off");
          display.print("    ");
          display.print("set");
          display.print("    ");
          display.setTextColor(BLACK, WHITE);
          display.print("cooling");
          break;
      
    }
  
    display.display();
}





void setTemp(int mode)
{
   button1State = digitalRead(button1);
   button2State = digitalRead(button2);
  if (desiredTemp == 0 || mode == 1)
  {
    desiredTemp = currentTemp;
  }
  if ((button2State == 0)  && ((mode == 2) || (mode == 3)))
  {
    desiredTemp = desiredTemp + 0.05;
    
  }

  if ((button1State == 0) && ((mode == 2) || (mode == 3)))
  {
    desiredTemp = desiredTemp - 0.05;
  }
}




void displayDesiredTemp()
{
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0, 25);
    display.println("Desired Temp:");
    display.setTextSize(2);
    display.println(desiredTemp);
    display.display();
     
}


void draw_text(byte x_pos, byte y_pos, char *text, byte text_size) {
  display.setCursor(x_pos, y_pos);
  display.setTextSize(text_size);
  display.print(text);
  display.display();
}

void displayRTC()
{
    char buf[40];
    //time_t t = myRTC.get();
    float celsius = myRTC.temperature() / 4.0;
    currentTemp = celsius * 9.0 / 5.0 + 32.0;
    //sprintf(buf, "%.2d:%.2d:%.2d %.2d%s%d ",
       // hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), year(t));
    //Serial.print(buf);
    //Serial.print(celsius);
    //Serial.print("C ");
    //Serial.print(fahrenheit);
    //Serial.println("F");

   delay(50);
    

    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);

     
    display.setCursor(0, 0);
    display.println("Current Temp:");
   

     
    display.setTextSize(2);
    display.println(currentTemp);
     
    display.display();
}
