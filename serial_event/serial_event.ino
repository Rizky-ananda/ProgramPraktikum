#include <SoftwareSerial.h>

#define SSerialRX         16
#define SSerialTX         17
#define SSerialTxControl  4
#define RS485Transmit     HIGH
#define RS485Receive      LOW

SoftwareSerial RS485Serial(SSerialRX, SSerialTX);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, RS485Transmit);
  digitalWrite(SSerialTxControl, RS485Receive);
  RS485Serial.begin(9600);
}

void loop() {
  //peran transmitter
  if(Serial.available()) {
    String input = Serial.readString();
    RS485Serial.write(input.c_str());
    digitalWrite(SSerialTxControl, RS485Receive);
    Serial.write(input.c_str());
  }
  //peran receiver
  if(RS485Serial.available()) {
    char receivedChar = (char)RS485Serial.read();
    Serial.write(receivedChar);
  }

}