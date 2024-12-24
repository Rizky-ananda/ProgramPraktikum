//  master code
#include <SoftwareSerial.h>

#define RX_PIN 16 // MAX485 RX pin
#define TX_PIN 17 // MAX485 TX pin
#define DRE_PIN 4 // MAX485 DE pin
#define pinPot 15
// #define RE_PIN 5 // MAX485 RE pin


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
}

void loop() {
  // Master code

  int bacaanPotensio = analogRead(15);
  String input = Serial.readString();

  digitalWrite(DRE_PIN, HIGH);
  Serial.println(bacaanPotensio);
  mySerial.print("com3: "+ input + String(bacaanPotensio));
  digitalWrite(DRE_PIN, LOW); 

  

  // ilmu ngobrol
  // if (Serial.available()){
  //   int bacaanPotensio = analogRead(13);
  //   String input = Serial.readString();
  //   digitalWrite(DRE_PIN, HIGH);
  //   Serial.println(input);
  //   mySerial.print("ESP 1: "+ input + String(bacaanPotensio));
  //   digitalWrite(DRE_PIN, LOW); 
  // }

  // slave code
  // if (mySerial.available()) {
  //   String message = mySerial.readString();
  //   Serial.println(message);
  // }
  delay(1000);
}