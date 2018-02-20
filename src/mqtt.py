import paho.mqtt.client as mqtt
import json
import logging

LOGGER = logging.getLogger('mqtt')

class MqttClient(object):
  def __init__(self, config):
    self.config = config
    self.client = mqtt.Client()
    self.subscriptions = {}

    self.client.on_connect = self.on_connect
    self.client.on_message = self.on_message

    if 'username' in config:
      self.client.username_pw_set(config['username'], config['password'])
    self.client.connect(config['host'], config['port'], 60)
    self.client.loop_start()

  def publish(self, topic, message):
    self.client.publish(
      topic=topic,
      payload=message,
      qos=2
    )

  def subscribe(self, topic, callback):
    if not topic in self.subscriptions:
      self.subscriptions[topic] = []
    self.subscriptions[topic].append(callback)

  def on_connect(self, client, userdata, flags, rc):
    LOGGER.info("Connected: {}".format(rc))
    for topic in self.subscriptions:
      LOGGER.info("Subscribing: {}".format(topic))
      client.subscribe(topic)

  def on_message(self, client, userdata, msg):
    if msg.topic in self.subscriptions:
      LOGGER.info("Triggering callbacks for: {}".format(msg))
      for callback in self.subscriptions[msg.topic]:
        callback(msg.topic, str(msg.payload))
    else:
      LOGGER.info("Got message: {}".format(msg))
