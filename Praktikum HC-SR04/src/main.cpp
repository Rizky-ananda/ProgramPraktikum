#include <Arduino.h>

/* Praktikum Pengukuran jarak menggunakan sensor HC-SR04
  cek suhu (dalam celsius) untuk mendapatkan besaran laju bunyi
  laju bunyi = kelajuan gelombang bunyi yang merambat pada medium elastisitas
  contoh suhu 20 C = 343 m/detik
  cek di https://www.omnicalculator.com/physics/speed-of-sound 
  persamaan mendapatkan jarak dengan sensor yaitu = (duration * laju bunyi * 10000) / 2 Hasilnya dalam cm
  */


// Library Oled
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



// Mendefinisikan Pin HC-SR04
#define PIN_TRIG 5
#define PIN_ECHO 18


// Mendefinisikan Layar Oled dan memasukan alamat I2C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
// alamat I2C
#define SCREEN_ADDRES 0x3C
// Inisialisasi oled
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {

  Serial.begin(9600);
  // Setup pin Trig dan Echo
  pinMode (PIN_TRIG, OUTPUT);
  pinMode (PIN_TRIG, INPUT);

  // Cek Oled
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRES)){
    Serial.println(F("SSD1306 allocation failed!"));
    for(;;);
  }
  
  // Setup Oled
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  // Start a new measurement:

  // on/off sinyal Trig
  // menyalakan sinyal trig
  digitalWrite(PIN_TRIG, HIGH);
  // delay sinyal (10 ms)
  delayMicroseconds(10);
  // mematikan sinyal trig
  digitalWrite(PIN_TRIG, LOW);

  // Read the result:
  // deklarasikan echo dengan fungsi pulseIn
  int duration = pulseIn(PIN_ECHO, HIGH);
  float jarak = (duration * 345.65 / 10000) / 2;
  
  // cetak hasil pembacaan
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");
  // Serial.print(" Distance in inches: ");
  // Serial.println(duration / 148);

  // cetak hasil pembacaan di oled
  display.clearDisplay();
  display.setCursor(30,0);
  display.print("Pengukuran Jarak");
  display.setCursor(15,10);
  display.print("Kelompok 2: Rizky");
  display.setCursor(0,30);
  display.print("Jarak " + String(jarak) + " Cm");

  // display.setCursor(0,40);
  // display.print("Dalam Inci   = " + String(duration / 148) + " In");
  delay(1000);
  
}