#include "MQTT.h"

SYSTEM_THREAD(ENABLED);

void callback(char* topic, byte* payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

void setup() {
  Serial.begin(9600);
  while (!Serial.isConnected()) {}
}

void loop() {
  if (clinet.isConnected()) {
    client.loop();
  } else {
    client.connect(System.deviceID());
    client.subscribe("iot2023");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(payload);
}