#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>


// set the LCD number of columns and rows
#define pinSoil 4
#define pinRelay 13

int lcdColumns = 16;
int lcdRows = 2;
int c = 0; // counter


LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

String checkMoisture(int analogValue){
  if(analogValue < 1600){
    return "BASAH";
  }
  else if(analogValue >= 1200 && analogValue <= 2400){
    return "NORMAL";
  }
  else{
    return "KERING";
  }
}

// Nama wifi dan Password
const char* ssid = "broker24";
const char* password = "broker24";

// MQTT Broker
const char* MQTT_username = NULL;
const char* MQTT_password = NULL;

// Menganti IP Address, supaya connect ke mqtt broker
const char* mqtt_server = "192.168.1.211";
const char* mqtt_topic = "SOIL/1";
const int mqtt_port = 1883;

// Wifi
WiFiClient espClient;
PubSubClient client(espClient);

void setup(){
  // initialize LCD
  pinMode (pinRelay, OUTPUT);
  digitalWrite(pinRelay, LOW);
  Serial.begin(9600);
  // setup wifi
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // lcd.init();
  // //turn on LCD backlight                      
  // lcd.backlight();
  // lcd.clear();

}

void loop(){
  // set cursor to first column, first row
  if(!client.connected()){
    reconnect();
  }
  if(!client.loop()){
    client.connect("ESP32Client", MQTT_username, MQTT_password);

  }
  String nomorClient = "Client_48";

  float bacaan = analogRead(4);
  // // mengirim ke broker
  // char datapayload[100];.
  c++;
  String status = checkMoisture(bacaan);
  String datapayload = String(c) + "). Tingkat Kelembaban: " + String(bacaan) + " , Status: " + status;
  // sprintf(datapayload, "%d). Tingkat kelembaban: %d, status: %s",c,bacaan, status.c_str());
  client.publish(mqtt_topic, datapayload.c_str());

  Serial.print("#");Serial.print(String(c));
  Serial.print(" Topik: ");Serial.print(mqtt_topic);
  Serial.print(" , Pesan: ");Serial.println(datapayload.c_str());
  delay(1000);


  // // Serial.println("Bacaan: " + String(bacaan) + " " + checkMoisture(bacaan));
  // if (checkMoisture(bacaan) == "KERING"){
  //   digitalWrite(pinRelay, LOW);
  // }
  // else{
  //   digitalWrite(pinRelay, HIGH);
  // }
  // lcd.setCursor(0, 0);
  // // print message
  // lcd.print("Bacaan Sensor");
  // //delay(1000);
  // // clears the display to print new message
  // // lcd.clear();
  // // set cursor to first column, second row
  // lcd.setCursor(0,1);
  // lcd.print(checkMoisture(bacaan));
  // delay(1000);
  // lcd.clear(); 
}

void setup_wifi(){ 
  delay(10); 
  // Set your Static IP address + gateway 
  IPAddress local_IP(192, 168, 1, 48); //xxx ganti dgn nomor NPM terakhir 
  IPAddress gateway(192, 168, 1, 1); 
   
  IPAddress subnet(255, 255, 255, 0); 
  IPAddress primaryDNS(8, 8, 8, 8);   //optional 
  IPAddress secondaryDNS(192, 168, 1, 1); //optional 
   
  // Configures static IP address 
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) { 
    Serial.println("STA Failed to configure"); 
  } 
   
  // We start by connecting to a WiFi network 
  Serial.println(); 
  Serial.print("Connecting to ");Serial.println(ssid); 
   
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print("."); 
  } 
  Serial.println(""); 
  Serial.print("WiFi connected - ESP IP address: "); 
  Serial.println(WiFi.localIP()); 
} 
 
void callback(char* topic, byte* message, unsigned int length) { 
  // Handle MQTT callback if needed 
} 
 
void reconnect() { 
  // Loop until we're reconnected 
  while (!client.connected()){ 
    Serial.print("RE-connect to mqtt..."); 
    // Attempt to connect 
    if (client.connect("ESP32Client")){ 
      Serial.println("connected!"); 
    } else { 
      Serial.print("gagal, rc="); 
      Serial.print(client.state()); 
      Serial.println(" tunggu 5 detik..."); 
      delay(5000); 
    } 
  } 
}
