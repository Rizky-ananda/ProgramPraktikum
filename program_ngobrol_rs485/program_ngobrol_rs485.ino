// #include <Arduino.h>

//Masukan Library Yang Digunakan
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // bool status;
  // status = bme.begin(0x76);
  // if(!status){
  //   Serial.println("gagal membaca sensor");
  //   while(1);
  // }
}

void loop() {
  // put your main code here, to run repeatedly:

  float suhu = bme.readTemperature();
  float kelembaban = bme.readHumidity();

  bool status;
  status = bme.begin(0x76);
  if(!status){
    Serial.println("gagal membaca sensor");
    while(1);
  }

  Serial.print("Suhu: " + String(suhu) + " C");
  Serial.print("\t");
  Serial.println("Kelembaban: " + String(kelembaban) + " %");

  delay(400);

}

// #include <Wire.h>

// void setup() {
//   Wire.begin();
//   Serial.begin(9600);
//   Serial.println("Scanning I2C devices...");
// }

// void loop() {
//   byte error, address;
//   int nDevices = 0;

//   for (address = 1; address < 127; address++) {
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();

//     if (error == 0) {
//       Serial.print("Device ditemukan di alamat 0x");
//       if (address < 16) Serial.print("0");
//       Serial.print(address, HEX);
//       Serial.println();
//       nDevices++;
//     }
//   }
//   if (nDevices == 0) Serial.println("Tidak ada perangkat I2C ditemukan\n");
//   else Serial.println("Selesai scan\n");

//   delay(500);
// }
