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

#define  button1 9 //down temp; button states will be inverted since using internal pull-up resistor
#define  button2 8 //up temp

#define IR_SEND_PIN A5

IRsend irsend;

//irsend.enableIROut(A5); //no longer needed


  int button1State;
  int button2State;
  float desiredTemp;
  float currentTemp;
  int mode = 1; //for which cooling mode
  int fanOn = 0; //0 for off, 1 for on
   
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

  if (mode == 1) //off mode
  {
    button1State = digitalRead(button1);
    button2State = digitalRead(button2);
 
    while (button2State != 0) //stays in this loop until button 2 is pressed
    {
 
      button1State = digitalRead(button1);
      button2State = digitalRead(button2);
      if (button1State == 0) {
      switch (mode)
      {
        case 1: mode = 2;
                break;
        case 2: mode = 1;
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

  fanOn = decideToggle(desiredTemp, currentTemp, mode, fanOn); 
  
  
}



//decides if the fan should be toggled on or off; returns values according to its action 
int decideToggle(float desiredTemp, float currentTemp, int mode, int fanOn)
{
  if (((currentTemp - desiredTemp) > .5) && (mode == 2) && (fanOn == 0)) {
    sendIR(); //turn on
    Serial.println("Turning on");
    display.display();
    return 1;
  }

  
  if (((currentTemp - desiredTemp) <= -0.5) && (fanOn == 1)) {
    sendIR();
    Serial.println("Turning off");
    return 0;
  }

  else {
    return fanOn; //returns what it currently is, when it was passed in
  }
}


//sends the ir signal
void sendIR()
{
  
   int khz = 38;// 38kHz carrier frequency for the NEC protocol
   unsigned int On[] ={1250,400, 1250,400, 450,1250, 1250,400, 1250,400, 450,1250, 400,1250, 450,1200, 450,1250, 400,1250, 450,1200, 1300};  // Power 
   

   for (int i = 0; i < 10; i++) //need to play around with this value //************
   {
    irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   }
  // Serial.println("Toggled");
/*
   for (int i = 0; i < 10; i++) //need to play around with this value
   {
     irsend.sendRaw(On,sizeof(On)/sizeof(int),khz);
   }

 */
}

//displays the current mode
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
          break;

        case 2:
          display.setTextColor(WHITE, BLACK);
          display.print("off");
          display.print("    ");
          display.setTextColor(BLACK, WHITE);
          display.print("set");
          display.setTextColor(WHITE, BLACK);
          display.print("    ");
          break;
      
    }
  
    display.display();
    
}

//changes the desired temp based off of the buttons
void setTemp(int mode)
{
   button1State = digitalRead(button1);
   button2State = digitalRead(button2);
  if (desiredTemp == 0 || mode == 1)
  {
    desiredTemp = currentTemp;
  }
  if ((button2State == 0)  && ((mode == 2) ))
  {
    desiredTemp = desiredTemp + 0.05;
    
  }

  if ((button1State == 0) && ((mode == 2) ))
  {
    desiredTemp = desiredTemp - 0.05;
  }
}

//displays the desired temp
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

//fxn for writing text on oLED
void draw_text(byte x_pos, byte y_pos, char *text, byte text_size) {
  display.setCursor(x_pos, y_pos);
  display.setTextSize(text_size);
  display.print(text);
  display.display();
}

//manipulates data and disaplays frm RTC
void displayRTC()
{
    char buf[40];
    //time_t t = myRTC.get();
    float celsius = myRTC.temperature() / 4.0;
    currentTemp = celsius * 9.0 / 5.0 + 32.0;
  
   delay(50);
   
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);

    display.setCursor(0, 0);
    display.println("Current Temp:");
     
    display.setTextSize(2);
    display.println(currentTemp);
     
    display.display();
}
