#include <EEPROM.h>

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "credentials.h"

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIN_LED_STRIP, NEO_GRB + NEO_KHZ800);

#include "connection.h"
#include "effects.h"
#include "button.h"
#include "state.h"

void on_mqtt_message(char* topic, byte* payload, unsigned int length) {
  char rawMessage[length + 1];
  for (int i = 0; i < length; i++) {
    rawMessage[i] = (char)payload[i];
  }
  rawMessage[length] = '\0';

  String message = String(message);
  String topic = String(topic);

  if (topic == MQTT_TOPIC_PRESENCE) {
    turnOnOff(message);
  } else if (topic == MQTT_TOPIC_PRESENCE) {
    turnOnOff(message);
  } else if (topic == MQTT_TOPIC_BUILD) {
    switchToState(message)
  } else {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.println("] ");
    Serial.print("Message:");
    Serial.println(message);
  }
}

void setup() {
  pinMode(PIN_STATUS_LED, OUTPUT);
  pinMode(PIN_ACTION_BUTTON, INPUT);
  digitalWrite(PIN_STATUS_LED, LOW);

  Serial.begin(115200);
  delay(10);

  strip.begin();
  strip.setBrightness(0);
  strip.show();

  client.setServer(MQTT_HOST, MQTT_PORT);
  client.setCallback(on_mqtt_message);
  colorWipe(strip.Color(0, 0, 0), 50);
}

void loop() {
  if (client.connected()) {
    client.loop();
    ArduinoOTA.handle();
    if (actionButtonPressed()) {
      Serial.println("Pressed a button!");
      colorWipe(strip.Color(255, 0, 0), 50);
      theaterChase(strip.Color(127, 127, 127), 50);
    }
  } else {
    if (ensureMqttConnection()) {
      onConnect();
    }
  }
}
