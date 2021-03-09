/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char Time[]     = "  :  :  ";
  char Calendar[] = "  /  /20  ";
  char temperature[] = " 00.00";
  char temperature_msb;
  byte i, second, minute, hour, day, date, month, year, temperature_lsb;

void setup(){
  Serial.begin(115200);
  
 

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  delay(2000);

  display.setFont(&FreeSerif9pt7b);
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(WHITE);        
  display.setCursor(0,20);             
  //display.println("Hello, world!");
  //display.println("Line 2");
 
 
  display.display();
  delay(2000); 
}

void draw_text(byte x_pos, byte y_pos, char *text, byte text_size) {
  display.setCursor(x_pos, y_pos);
  display.setTextSize(text_size);
  display.print(text);
  display.display();
}

void display_temp()
{
  if(temperature_msb < 0){
    temperature_msb = abs(temperature_msb);
    temperature[0] = '-';
  }
  else
    temperature[0] = ' ';
  temperature_lsb >>= 6;
  temperature[2] = temperature_msb % 10  + 48;
  temperature[1] = temperature_msb / 10  + 48;
  if(temperature_lsb == 0 || temperature_lsb == 2){
    temperature[5] = '0';
    if(temperature_lsb == 0) temperature[4] = '0';
    else                     temperature[4] = '5';
  }
  if(temperature_lsb == 1 || temperature_lsb == 3){
    temperature[5] = '5';
    if(temperature_lsb == 1) temperature[4] = '2';
    else                     temperature[4] = '7';
  
}
draw_text(75, 55, temperature, 1); 
Serial.println("display temp");
}



  
void loop() {
   // Write data to DS3231 RTC
    Wire.beginTransmission(0x68);               // Start I2C protocol with DS3231 address
    Wire.write(0);                              // Send register address
    Wire.write(0);                              // Reset sesonds and start oscillator
    Wire.write(minute);                         // Write minute
    Wire.write(hour);                           // Write hour
    Wire.write(day);                            // Write day
    Wire.write(date);                           // Write date
    Wire.write(month);                          // Write month
    Wire.write(year);                           // Write year
    Wire.endTransmission();                     // Stop transmission and release the I2C bus
    delay(200);                                 // Wait 200ms
  
 
  Wire.beginTransmission(0x68);                 // Start I2C protocol with DS3231 address
  Wire.write(0);                                // Send register address
  Wire.endTransmission(false);                  // I2C restart
  Wire.requestFrom(0x68, 7);                    // Request 7 bytes from DS3231 and release I2C bus at end of reading
  second = Wire.read();                         // Read seconds from register 0
  minute = Wire.read();                         // Read minuts from register 1
  hour   = Wire.read();                         // Read hour from register 2
  day    = Wire.read();                         // Read day from register 3
  date   = Wire.read();                         // Read date from register 4
  month  = Wire.read();                         // Read month from register 5
  year   = Wire.read();                         // Read year from register 6
  Wire.beginTransmission(0x68);                 // Start I2C protocol with DS3231 address
  Wire.write(0x11);                             // Send register address
  Wire.endTransmission(false);                  // I2C restart
  Wire.requestFrom(0x68, 2);                    // Request 2 bytes from DS3231 and release I2C bus at end of reading
  temperature_msb = Wire.read();                // Read temperature MSB
  temperature_lsb = Wire.read();                // Read temperature LSB
  display_temp();
 
}
