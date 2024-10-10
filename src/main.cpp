#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ilfandkym";         //wi-fi ssid
const char* password = "94263770";      //wi-fi password
#define mqtt_server "192.168.68.100"

#define test_topic "test/one"

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  client.setServer(mqtt_server, 1883);
  //Looping until WiFi is connected
  while (WiFi.status() != WL_CONNECTED)     //WL_CONNECTED IS A ENUM w/ VALUE = 3
    delay(50);
    Serial.print(".");

  Serial.print("");
  Serial.println("Wifi connected.");
}

void reconnect() {
  while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");

  if (client.connect("ESPClient")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
        reconnect();
      }
  client.loop();
  int data = 1;
  client.publish(test_topic, String(data).c_str(), true);
  delay(2000);

  }

