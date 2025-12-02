#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "DHT.h"   // library DHT bawaan Arduino IDE

#define DHTPIN 27   // pin data DHT terhubung ke GPIO15 (ubah sesuai sambunganmu)
#define DHTTYPE DHT22   // atau DHT22 jika sensormu DHT22

DHT dht(DHTPIN, DHTTYPE);

/*
Uncomment and set up if you want to use custom pins for the SPI communication
#define REASSIGN_PINS
int sck = -1;
int miso = -1;
int mosi = -1;
int cs = -1;
*/

// --- Fungsi umum SD Card ---
void writeFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Menulis file: %s\n", path);
  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Gagal membuka file untuk menulis");
    return;
  }
  if (file.print(message)) {
    Serial.println("File berhasil ditulis");
  } else {
    Serial.println("Gagal menulis file");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message) {
  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Gagal membuka file untuk menambah data");
    return;
  }
  if (file.print(message)) {
    Serial.println("Data berhasil ditambahkan");
  } else {
    Serial.println("Gagal menambahkan data");
  }
  file.close();
}

// --- Setup ---
void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Inisialisasi SD Card...");

#ifdef REASSIGN_PINS
  SPI.begin(sck, miso, mosi, cs);
  if (!SD.begin(cs)) {
#else
  if (!SD.begin()) {
#endif
    Serial.println("Gagal memuat SD card!");
    return;
  }

  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("Tidak ada SD card terpasang.");
    return;
  }

  Serial.print("Tipe SD Card: ");
  if (cardType == CARD_MMC) Serial.println("MMC");
  else if (cardType == CARD_SD) Serial.println("SDSC");
  else if (cardType == CARD_SDHC) Serial.println("SDHC");
  else Serial.println("Tidak diketahui");

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("Ukuran SD Card: %lluMB\n", cardSize);

  // Inisialisasi sensor DHT
  dht.begin();
  Serial.println("Sensor DHT siap digunakan.");

  // Membuat file DHT.txt untuk menyimpan data
  writeFile(SD, "/DHT.txt", "=== Data Sensor DHT (Suhu & Kelembapan) ===\n");
  Serial.println("File DHT.txt siap digunakan.\n");

  Serial.printf("Kapasitas total: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Kapasitas terpakai: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

// --- Loop utama ---
void loop() {
  float suhu = dht.readTemperature();     // Baca suhu (°C)
  float kelembapan = dht.readHumidity();  // Baca kelembapan (RH%)

  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("Gagal membaca data dari sensor DHT!");
    delay(2000);
    return;
  }

  // Tampilkan ke Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" °C  |  Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");

  // Simpan ke file DHT.txt di SD Card
  String data = "Suhu: " + String(suhu, 1) + "°C | Kelembapan: " + String(kelembapan, 1) + "%\n";
  appendFile(SD, "/DHT.txt", data.c_str());

  delay(1000); // 
}