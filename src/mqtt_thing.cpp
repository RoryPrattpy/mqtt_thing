/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/admin/CTD_2023/mqtt_thing/src/mqtt_thing.ino"
#include "MQTT.h"
#include "oled-wing-adafruit.h"

void setup();
void loop();
void resetDisplay();
void displayButtonStates();
#line 4 "/Users/admin/CTD_2023/mqtt_thing/src/mqtt_thing.ino"
SYSTEM_THREAD(ENABLED);

void callback(char* topic, byte* payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

OledWingAdafruit display;

bool buttonStateA = false;
bool buttonStateB = false;
bool buttonStateC = false;

bool clientButtonStateA = false;
bool clientButtonStateB = false;
bool clientButtonStateC = false;

void setup() {
  display.setup();
  display.clearDisplay();
  display.println("Connecting...");
  display.display();

  pinMode(D7, OUTPUT);

  Serial.begin(9600);
  while (!Serial.isConnected()) {}
}

void loop() {
  display.loop();
  if (client.isConnected()) {
    client.loop();

    if (display.pressedA()) {
      client.publish("inTopic/HipposAreVeryTasty/A", "m");
    }
    if (display.pressedB()) {
      client.publish("inTopic/HipposAreVeryTasty/B", "m");
    }
    if (display.pressedC()) {
      client.publish("inTopic/HipposAreVeryTasty/C", "m");
    }

    displayButtonStates();
  } else {
    client.connect(System.deviceID());
    client.subscribe("inTopic/HipposAreVeryTasty/Led");
    client.subscribe("inTopic/HipposAreVeryTasty/A");
    client.subscribe("inTopic/HipposAreVeryTasty/B");
    client.subscribe("inTopic/HipposAreVeryTasty/C");
  }
}

void resetDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
}

void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;

  if (String(topic).equals("inTopic/HipposAreVeryTasty/A")) {
    buttonStateA = !buttonStateA;
  }
  if (String(topic).equals("inTopic/HipposAreVeryTasty/B")) {
    buttonStateB = !buttonStateB;
  }
  if (String(topic).equals("inTopic/HipposAreVeryTasty/C")) {
    buttonStateC = !buttonStateC;
  }

  if (String(topic).equals("inTopic/HipposAreVeryTasty/Led")) {
    if (String(p).equals("1")) {
      digitalWrite(D7, 1);
    } else if (String(p).equals("0")) {
      digitalWrite(D7, 0);
    } else {
      Serial.println("failed");
    }
  }
}

void displayButtonStates() {
  resetDisplay();
  display.print("Button A: ");
  display.println(buttonStateA);
  display.print("Button B: ");
  display.println(buttonStateB);
  display.print("Button C: ");
  display.println(buttonStateC);
  display.display();
}