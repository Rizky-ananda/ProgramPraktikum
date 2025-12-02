/* PRAKTIKUM TEKNIK PENGUKURAN DAN INSTRUMENTASI
   MATERI PENGUKURAN CAHAYA RUANGAN MENGGUNAKAN LDR */

// definisikan variabel
byte pinSensor = ;
float tegangan;
float lux;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  float bacaanSensor = analogRead(pinSensor);
  tegangan = (bacaanSensor/4095) *3.3;
  lux = -1.3157*bacaanSensor + 4725;
  // lux = -0.4574*bacaanSensor + 1665.5;
  // lux = 21.042*exp(0.0017*bacaanSensor);

  Serial.print("Nilai_Analog:");Serial.print(bacaanSensor);
  Serial.print("\t");
  Serial.print("tegangan:");Serial.print(tegangan);
  Serial.print("\t");
  Serial.print("lux:");Serial.println(lux);

  delay(500);
 

}
