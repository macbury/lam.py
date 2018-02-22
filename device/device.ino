#include <EEPROM.h>

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "credentials.h"

const byte TICK_DELAY = 33;
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIN_LED_STRIP, NEO_GRB + NEO_KHZ800);

#include "effects.h"
#include "connection.h"
#include "button.h"
#include "state.h"

void on_mqtt_message(char* rawTopic, byte* payload, unsigned int length) {
  char rawMessage[length + 1];
  for (int i = 0; i < length; i++) {
    rawMessage[i] = (char)payload[i];
  }
  rawMessage[length] = '\0';

  String message = String(rawMessage);
  String topic = String(rawTopic);

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.println("Message: ");
  Serial.println(message);
  if (topic == MQTT_TOPIC_PRESENCE) {
    Serial.println("Topic presence");
    turnOnOff(rawMessage);
  } else if (topic == MQTT_TOPIC_BRIGHTNESS) {
    Serial.println("Changing brightness");
    setBrightness(message.toInt());
  } else if (topic == MQTT_TOPIC_BUILD) {
    switchToState(rawMessage);
  } else {
    Serial.println("Unhandled!");
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);

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
    clearColor();
    if (ensureMqttConnection()) {
      onConnect();
    }
  }

  delay(TICK_DELAY);
}
