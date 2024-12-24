// Masukan library yang dibutuhkan 

// Library DHT
#include <DHT.h>

// Library OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// definisikan variabel yang diguanakan 
// DHT
#define DHTPIN 4
#define DHTTYPE DHT22

// OLED (ukuran screen)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

float rh;
float suhu;

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  // inisialisasi objek display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    // alamat I2C default
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
  // membaca kelembaban 
  float rh = dht.readHumidity();
      // membaca suhu satuan celsius
  float suhu = dht.readTemperature();

  // menampilkan di serial monitor 
  if (isnan(suhu) || (isnan(rh))) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Hasil Pembacaan Sensor : ");
    Serial.print("Suhu ");
    Serial.print(suhu);
    Serial.print(" C");

    Serial.print(" RH ");
    Serial.print(rh);
    Serial.println(" %");
  }

  // menampilkan pda display
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("kelompok 2");

  // display.clearDisplay();
  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(0,2);
  // display.print("Suhu");
  // display.print(suhu);
  // display.println("RH:" + String (rh));
  display.display();


  delay(1000);

}
