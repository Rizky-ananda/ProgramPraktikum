//  slave code 
#include <SoftwareSerial.h>

#define RX_PIN 16 // MAX485 RX pin
#define TX_PIN 17 // MAX485 TX pin
#define DRE_PIN 4 // MAX485 DE pin

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// #define RE_PIN 5 // MAX485 RE pin
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRES 0x3C // alamat I2C
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, OLED_RESET);


SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX
// String inputString = "";
// bool stringComplate = false;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(DRE_PIN, OUTPUT);
  pinMode(DRE_PIN, OUTPUT);
  digitalWrite(DRE_PIN, HIGH);
  digitalWrite(DRE_PIN, LOW);
  // inputString.reserve(200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRES)){
     Serial.println(F("SSD1306 allocation failed"));
     for(;;);
   }
   display.clearDisplay();
   display.setTextSize(1);
   display.setTextColor(WHITE);
}

void loop() {
  // Master code
  
  // if (Serial.available()){
  //   // int bacaanPotensio = analogRead(13);
  //   String input = Serial.readString();
  //   digitalWrite(DRE_PIN, HIGH);
  //   Serial.println(input);
  //   mySerial.print("com15: "+ input + String(bacaanPotensio));
  //   digitalWrite(DRE_PIN, LOW); 
  // }

  // slave code
  if (mySerial.available()) {
    String message = mySerial.readString();
    Serial.println(message);

    display.clearDisplay();
    display.setCursor(10,0);
    display.print("KOmunikasi Serial"); 
    display.setCursor(10,20);
    display.print("Kelompok 2 A1");
    display.setCursor(0,40);
    display.print(message);
    display.display();
  }

  

  
  // delay(1000);

}