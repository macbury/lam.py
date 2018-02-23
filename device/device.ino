#include <EEPROM.h>

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "credentials.h"

const byte TICK_DELAY = 10;
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIN_LED_STRIP, NEO_GRB + NEO_KHZ800);

#include "effects.h"
#include "connection.h"
#include "button.h"
#include "state.h"

void on_mqtt_message(char* topic, byte* payload, unsigned int length) {
  char message[length + 1];
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.println("Message: ");
  Serial.println(message);
  if (strcmp(topic, MQTT_TOPIC_PRESENCE) == 0) {
    Serial.println("Topic presence");
    turnOnOff(message);
  } else if (strcmp(topic, MQTT_TOPIC_BRIGHTNESS) == 0) {
    Serial.println("Changing brightness");
    setBrightness(String(message).toInt());
  } else if (strcmp(topic, MQTT_TOPIC_BUILD) == 0) {
    switchToState(message);
  } else {
    Serial.println("Unhandled!");
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);

  randomSeed(100);
  pinMode(PIN_STATUS_LED, OUTPUT);
  pinMode(PIN_ACTION_BUTTON, INPUT);
  analogWrite(PIN_STATUS_LED, 255);

  client.setServer(MQTT_HOST, MQTT_PORT);
  client.setCallback(on_mqtt_message);

  strip.begin();
  delay(100);
  clearColor();
}

void loop() {
  if (client.connected()) {
    client.loop();
    ArduinoOTA.handle();
    handleButton();
    handleLight();
  } else {
    if (ensureMqttConnection()) {
      onConnect();
    }
  }

  delay(TICK_DELAY);
}
