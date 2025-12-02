/*
  Project: Publish data Pembacaan DHT ke Broker MQTT
  
*/
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

// DHT
#define dht_pin 14
#define DHTTYPE DHT22
DHT dht(dht_pin, DHTTYPE);
int c = 0;

// nama wifi dan pass
const char* ssid = "hidroponik21b";
const char* password = "squitto4kses";

// MQTT broker 
const char* MQTT_username = NULL;
const char* MQTT_password = NULL;

// Menganti variable pada raspberry pi ip addres, supaya connect ke mqtt broker
const char* mqtt_server = "192.168.2.211";
const char* mqtt_topic = "DHT/50"; //sesuaikan sama kelompok
const int mqtt_port = 1883;

// WiFi
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  dht.begin();
  // put your setup code here, to run once:
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
    reconnect();
  }
  if (!client.loop()){
    client.connect("ESP32Client", MQTT_username, MQTT_password);
  }

  String nomorClient = "Client_50"; // disesuaikan
  float suhu = dht.readTemperature();
  float rh = dht.readHumidity();
  // Serial.print("Suhu: " + String(suhu) + " C");
  // Serial.println("RH: " + String(suhu) + " %");
  
  // mengirim data ke broker
  char dataPayload[100]; // siapkan variabel char
 
  c++;
  sprintf(dataPayload, "%d). Suhu: %.2f, RH: %.2f",c,suhu,rh);
  client.publish(mqtt_topic, dataPayload);

  Serial.print("#");Serial.print(String(c));
  Serial.print(" Topik: ");Serial.print(mqtt_topic);
  Serial.print(" , Pesan: ");Serial.println(dataPayload);
  delay(1000);

}

void setup_wifi(){ 
  delay(10); 
  // Set your Static IP address + gateway 
  IPAddress local_IP(192, 168, 2, 61); //xxx ganti dgn nomor NPM terakhir 
  IPAddress gateway(192, 168, 2, 1); 
   
  IPAddress subnet(255, 255, 255, 0); 
  IPAddress primaryDNS(8, 8, 8, 8);   //optional 
  IPAddress secondaryDNS(192, 168, 2, 1); //optional 
   
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
