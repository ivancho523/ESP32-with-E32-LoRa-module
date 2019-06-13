// code for esp32 with e32 ebyte lora module
#include <HardwareSerial.h>                         //we have to include the HardwareSerial library, or else we can't use it
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define rx 16                                          //LORA TX
#define tx 17                                          //LORA RX
String incomingString;
String PrStr;                                           // String used to print the incoming string after decoding it

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     9 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

HardwareSerial myserial(1);

void setup() {
  Serial.begin(115200);
  myserial.begin(9600, SERIAL_8N1, rx, tx);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2);
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println("E32 TEST");
  display.display();
}

void loop() {
   if (myserial.available()){                 
        incomingString = myserial.readString();
        display.clearDisplay();
        display.setCursor(0,0);
        display.println(incomingString);
        display.display();
        myserial.println("Ack mess");
        delay(10);
    }
    delay(10);
}
