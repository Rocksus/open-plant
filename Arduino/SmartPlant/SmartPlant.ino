#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <dht.h>
//#define DEBUG

//Wifi SSID and password respectively
const char* ssid = "Nxtkh";
const char* password = "glnf5265";
const char* IP_ADDR = "192.168.43.168:8000/plants";

WiFiServer server(80);

dht DHT;

#define DHT11_PIN 13
#define SOIL_PIN A0
int soilMoistureValue = 0;

void setup(){
  delay(1000);
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  
  while(!Serial);

  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

   WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop()
{
  HTTPClient http;
  int chk = DHT.read11(DHT11_PIN);
  soilMoistureValue = analogRead(SOIL_PIN);
  #ifdef DEBUG
    Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
    Serial.print("Humidity = ");
    Serial.println(DHT.humidity);
    Serial.println(soilMoistureValue);
  #endif

  
   StaticJsonDocument<200> doc;
  
  doc["plant_id"]=1;
  doc["temp"]=DHT.temperature;
  doc["humidity"]=DHT.humidity;
  doc["moisture"]=soilMoistureValue;

    http.begin(IP_ADDR);
    http.addHeader("Content-Type", "application/json");
  String postData = "";
  serializeJson(doc, postData);
  int httpCode = http.POST(postData);
  String response = http.getString();
  #ifdef DEBUG
    Serial.print("HTTP Code: ");
    Serial.println(httpCode);
    Serial.print("Response: ");
    Serial.println(response);
  #endif
  delay(5000);
}