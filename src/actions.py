import random
import requests
import logging

LOGGER = logging.getLogger('actions')

class EmitCoffee():
  def __init__(self, mqtt, config):
    self.config = config
    self.accumulator = 0
    self.mqtt = mqtt
    self.coffee_count = 0

  def loop(self):
    if self.accumulator <= 0:
      self.emit()
      self.accumulator = 10
    else:
      self.accumulator -= 1

  def emit(self):
    coffee = requests.get(self.config['endpoint']).json()
    next_coffee_count = int(float(coffee['feeds'][-1]['field1']))
    if next_coffee_count > self.coffee_count:
      self.mqtt.publish(self.config['topic'], next_coffee_count)
    self.coffee_count = next_coffee_count

class EmitFood():
  def __init__(self, mqtt, config):
    self.config = config
    self.accumulator = 0
    self.mqtt = mqtt
    self.have_orders = False

  def loop(self):
    if self.accumulator <= 0:
      self.emit()
      self.accumulator = 10
    else:
      self.accumulator -= 1

  def emit(self):
    orders = requests.get(self.config['endpoint'], auth=(self.config['username'], self.config['password'])).json()
    next_orders = len(orders) > 0

    if next_orders != self.have_orders:
      self.have_orders = next_orders

      if self.have_orders:
        self.mqtt.publish(self.config['topic'], 'waiting')
      else:
        self.mqtt.publish(self.config['topic'], 'delivered')

class EmitStatus():
  def __init__(self, client, jenkins, topic):
    self.client = client
    self.topic = topic
    self.jenkins = jenkins
    self.accumulator = 0
    self.prev_status = None

  def loop(self):
    current_status = self.jenkins.status()
    if current_status != self.prev_status:
      self.prev_status = current_status
      self.client.publish(self.topic, current_status)

class EmitPresence():
  def __init__(self, client, hipchat, topic):
    self.client = client
    self.topic = topic
    self.hipchat = hipchat
    self.visible_timer = 0
    self.prev_status = None
    self.accumulator = 0

  def loop(self):
    if self.accumulator <= 0:
      current_status = self.status()

      if current_status != self.prev_status:
        self.visible_timer = 0
      else:
        self.visible_timer += 1;

      self.prev_status = current_status

      if self.visible_timer > 2:
        self.client.publish(self.topic, current_status)

      self.accumulator = 10
    else:
      self.accumulator -= 1

  def status(self):
    if self.hipchat.is_anybody_online():
      return "online"
    else:
      return "false"

class ButtonHandler():
  def __init__(self, mqtt, hipchat, config):
    self.mqtt = mqtt
    self.hipchat = hipchat
    self.topic = config['topic']
    self.recipient = config['recipient']
    self.messages = config['messages']

    self.mqtt.subscribe(self.topic, self.on_mqtt_message)

  def on_mqtt_message(self, topic, body):
    message = random.choice(self.messages)
    self.hipchat.message(self.recipient, message)
