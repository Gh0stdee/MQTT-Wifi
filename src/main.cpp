#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define ssid        //wi-fi ssid
#define password      //wi-fi password
#define mqtt_server "192.168.68.100"

#define test_topic "test/number"

WiFiClient espClient;

void setup() {
  Serial.begin(9600);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  client.setserver(mqtt_server, 1883);
  //Looping until WiFi is connected
  while (WiFi.status() != WL_CONNECTED)     //WL_CONNECTED IS A ENUM w/ VALUE = 3
    delay(50);
    Serial.print(".");

  Serial.print("");
  Serial.println("Wifi connected.");
}

void loop() {

  
  
  }

