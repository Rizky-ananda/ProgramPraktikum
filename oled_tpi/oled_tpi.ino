// Oled DHT11 dengan program millis

// Oled
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// DHT
#include <DHT.h>
// #define DHTPIN 14
#define DHTPIN 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRES 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Multitasking
unsigned long waktusblm1;
unsigned long waktusblm2;
unsigned long waktuskrg1;
unsigned long waktuskrg2;
const int jeda_monitor = 200;
const int jeda_oled = 1000;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRES)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

}

void loop() {
  // // put your main code here, to run repeatedly:
  waktuskrg1 = millis();
  waktuskrg2 = millis();
  float suhu = dht.readTemperature();
  float rh = dht.readHumidity();
  if (waktuskrg1 - waktusblm1 >= jeda_monitor) {
    Serial.print("Suhu: " + String(suhu));
    Serial.print(",");
    Serial.println("RH: " + String(rh));
    waktusblm1 = waktuskrg1;
  }

  if (waktuskrg2 - waktusblm2 >= jeda_oled){
    display.clearDisplay();
    display.setCursor(30,0);
    display.print("Suhu dan RH");
    display.setCursor(15,10);
    display.print("Kelompok 2: Rizky");
    display.setCursor(0,30);
    display.print("Suhu = " + String(suhu) + " C");
    display.setCursor(0,40);
    display.print("RH   = " + String(rh) + " %");
    display.display();
    waktusblm2 = waktuskrg2;
  }
}

