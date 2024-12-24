//#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define SPEED_OF_SOUND 0.0345

Adafruit_SSD1306 display(128,64,&Wire,-1) ;
unsigned long lastSerialOutput = 0, lastOLEDOutput = 0 ;
float jarak;

void setup() {
  Serial.begin (9600) ;
  pinMode (TRIG_PIN, OUTPUT) ;
  pinMode (ECHO_PIN, INPUT) ;

  // diaplay.begin(SSD1306_SWITCHCAPVCC, 0x3C) ;
  // display.setTextColor(WHITE) ;
  // display.clearDisplay() ;
}

void loop() {
  digitalWrite(TRIG_PIN, LOW) ;
  delayMicroseconds(2) ;
  digitalWrite(TRIG_PIN, HIGH) ;
  delayMicroseconds (10) ;
  digitalWrite(TRIG_PIN, LOW) ;
  int duration = pulseIn(ECHO_PIN, HIGH);

   // Hitung jarak (cm)
  // Kecepatan suara = 343 m/s = 34300 cm/s
  // Jarak = (durasi × kecepatan suara) / 2
  // Dibagi 2 karena pulsa pergi dan kembali
  float distance = (duration * 0.0343) / 2;
  // Output ke Serial Monitor setiap 300ms
  if (millis() - lastSerialOutput >= 300) {
    Serial.print("Jarak: ");
    Serial.print(distance);
    Serial.println(" cm");
    lastSerialOutput = millis();
  }
     // Output ke OLED display setiap 1000ms
  if (millis() - lastOLEDOutput >= 1000) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Pengukur Jarak");
    display.println("---------------");
    display.print("Jarak: ");
    display.print(distance);
    display.println(" cm");
    display.display();
    lastOLEDOutput = millis();
  }
}
