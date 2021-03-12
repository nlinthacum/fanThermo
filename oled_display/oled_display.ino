
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





void setup(){
  Serial.begin(9600);
  Wire.begin();
  
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
  delay(2000);
  displayRTC();
  delay(1000);
  
 

}




  
void loop() {
 displayRTC();
  
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
    float fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    sprintf(buf, "%.2d:%.2d:%.2d %.2d%s%d ",
        hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), year(t));
    Serial.print(buf);
    Serial.print(celsius);
    Serial.print("C ");
    Serial.print(fahrenheit);
    Serial.println("F");

    delay(1000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(fahrenheit);
  display.display();
}
