
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>




#include <DS3232RTC.h>      // https://github.com/JChristensen/DS3232RTC
DS3232RTC myRTC;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET 4

 #define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define  button1 8 //down temp; button states will be inverted since using internal pull-up resistor
#define  button2 9 //up temp



  int button1State;
  int button2State;
  float desiredTemp;
  float currentTemp;

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
  displayRTC();

  
 
}


  
void loop() {
 setTemp();
 displayRTC();
 displayDesiredTemp();
 displayMode(3);
 
 button1State= digitalRead(button1);
 Serial.print("Butoon 1: ");
 Serial.println(button1State);
 button2State= digitalRead(button2);
 Serial.print("Butoon 2: ");
 Serial.println(button2State);
 delay(5);
 

  
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

        case 2:
          display.setTextColor(WHITE, BLACK);
          display.print("off");
          display.print("    ");
          display.setTextColor(BLACK, WHITE);
          display.print("set");
          display.setTextColor(WHITE, BLACK);
          display.print("    ");
          display.print("cooling");

      case 3:
          display.setTextColor(WHITE, BLACK);
          display.print("off");
          display.print("    ");
          display.print("set");
          display.print("    ");
          display.setTextColor(BLACK, WHITE);
          display.print("cooling");
      
    }

   
   
  
    display.display();
}





void setTemp()
{
  if (desiredTemp == 0)
  {
    desiredTemp = currentTemp;
  }
  if (button2State == 0)
  {
    desiredTemp = desiredTemp + 0.05;
    
  }

  if (button1State == 0)
  {
    desiredTemp = desiredTemp - 0.05;
  }
  
}




void displayDesiredTemp()
{
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
   // display.setCursor(0, 0);
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
    time_t t = myRTC.get();
    float celsius = myRTC.temperature() / 4.0;
    currentTemp = celsius * 9.0 / 5.0 + 32.0;
    sprintf(buf, "%.2d:%.2d:%.2d %.2d%s%d ",
        hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), year(t));
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
