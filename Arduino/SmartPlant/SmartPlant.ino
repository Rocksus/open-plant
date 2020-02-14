#include <ESP8266WiFi.h>
#include <dht.h>

//Wifi SSID and password respectively
const char* ssid = "Nxtkh";
const char* password = "glnf5265";

WiFiServer server(80);

dht DHT;

#define DHT11_PIN 13
#define SOIL_PIN A0
int soilMoistureValue = 0;

void setup(){
  Serial.begin(115200);
  delay(10);
  
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
 
  // Start the server
  server.begin();
  Serial.println("Server started");

    // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  soilMoistureValue = analogRead(SOIL_PIN);
  Serial.println(soilMoistureValue);
  delay(5000);
}
