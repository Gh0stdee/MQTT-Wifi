#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ilfandkym";         //WiFi ssid
const char* password = "94263770";      //WiFi password

#define mqtt_server "192.168.68.100"    //set MQTT server to IP address
#define test_topic "test/one"           //set topic of the publishing message

//construct a WiFiclient that can connect to IP address(done here) or port sepcified by client.connect(IP or URL, Port no.)->returns true/false
WiFiClient espClient;            
//Take in a network client to construct a client that can publish and subscribe 
PubSubClient client(espClient);         


void setup() {
  //intiate serial communication
  Serial.begin(9600);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  //connect to WiFi
  WiFi.begin(ssid, password);

  //set address of server and connection port the client will connect to
  client.setServer(mqtt_server, 1883);

  //looping until WiFi is connected
  /*
  Return values of WiFi.status()
  WL_CONNECTED: Connected to WiFi network
  WL_CONNECT_FAILED: Fail to connect after number of attempts expires
  WL_IDLE_STATUS: Temporary staus that changes to CONNECTED/CONNECT_FAILED 
  WL_SCAN_COMPLETED
  WL_NO_SHIELD
  WL_NO_SSID_AVAIL
  WL_AP_CONNECTED
  WL_AP_LISTENING
  WL_CONNECTION_LOST
  WL_DISCONNECTED
  */
  while (WiFi.status() != WL_CONNECTED)   
    delay(50);
    Serial.print(".");

  //indicate connection of WiFi
  Serial.println("");
  Serial.println("WiFi connected.");
}

void reconnect() {
  while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");

    if (client.connect("ESPClient")) //connects the client with declared ID: returns true or false depends if connection succeeded
    {
      Serial.println("connected");
    } 
    else {
      Serial.print("failed, state=");
      Serial.print(client.state()); //check state to get information about error
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  //check whether client is connected
  if (!client.connected()) {
        reconnect();
      }
  
  
  client.loop(); //Process incoming messages and maintain connection with MQTT server
  int data = 1;
  //publish(topic, payload[message], length[optional], messageRetain[optional])
  client.publish(test_topic, String(data).c_str(), true);
  delay(2000);

  }

