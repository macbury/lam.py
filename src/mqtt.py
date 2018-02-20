import paho.mqtt.client as mqtt
import json
import logging

LOGGER = logging.getLogger('mqtt')

class MqttClient(object):
  def __init__(self, config):
    self.config = config
    self.client = mqtt.Client()

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

  def on_connect(self, client, userdata, flags, rc):
    LOGGER.info("Connected: {}".format(rc))
  def on_message(self, client, userdata, msg):
    LOGGER.info("Got message: {}".format(msg))

class EmitStatus():
  def __init__(self, client, topic):
    self.client = client
    self.topic = topic

  def run(self, status):
    self.client.publish(self.topic, status)

class ButtonHandler():
  def __init__(self, client, topic):
    self.client = client
    self.topic = topic
