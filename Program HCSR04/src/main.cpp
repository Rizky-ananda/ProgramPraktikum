#include <Arduino.h>

// Library Oled
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Mendefinisikan Pin HC-SR04
#define PIN_TRIG 5
#define PIN_ECHO 18

// Mendefinisikan Layar Oled
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRES 0x3C // alamat I2C
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRES)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  // Start a new measurement:
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // Read the result:
  int duration = pulseIn(PIN_ECHO, HIGH);
  float kalibrasi = 1.0226 *((duration * 345.65 / 10000) / 2);

  Serial.print("Distance in CM: ");
  Serial.print((duration * 345.65 / 10000) / 2 );
  Serial.print("  kalibrasi: ");
  Serial.println(kalibrasi );
  // Serial.print(" Distance in inches: ");
  // Serial.println(duration / 148);

  display.clearDisplay();
  display.setCursor(10,0);
  display.print("Pengukuran Jarak"); 
  display.setCursor(10,20);
  display.print("Kelompok 2: Rizky");
  display.setCursor(0,40);
  display.print("Dalam CM = " + String((duration * 345.65 / 10000) / 2 ) + " CM");
  display.setCursor(0,50);
  display.print("kalibrasi = " + String(kalibrasi) + " CM");
  // display.setCursor(0,40);
  // display.print("Dalam Inci   = " + String(duration / 148) + " In");
  display.display();

  delay(1000);
}