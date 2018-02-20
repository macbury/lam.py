import logging
import os
import time
from hipchat import Hipchat
from jenkins_client import JenkinsClient
from mqtt import MqttClient
from actions import EmitPresence, EmitStatus, ButtonHandler, EmitFood, EmitCoffee

from ruamel.yaml import YAML

LOGGER = logging.getLogger('lamp')
logging.basicConfig(
  level=logging.INFO,
  format="[%(asctime)s] %(levelname)s:%(name)s:%(message)s"
)

CONFIG_PATH = os.path.join('./', 'config.yaml')
LOGGER.info("Loading config: " + CONFIG_PATH)
CONFIG = YAML(typ='safe').load(open(CONFIG_PATH))

jenkins = JenkinsClient(CONFIG['jenkins'])
hipchat = Hipchat(CONFIG['hipchat'])
mqtt = MqttClient(CONFIG['mqtt'])

EMITTERS = [
  EmitStatus(mqtt, jenkins, CONFIG['jenkins']['topic']),
  EmitPresence(mqtt, hipchat, CONFIG['hipchat']['topic']),
  EmitFood(mqtt, CONFIG['lunching']),
  EmitCoffee(mqtt, CONFIG['coffee'])
]

ButtonHandler(mqtt, hipchat, CONFIG['button'])

# import code; code.interact(local=dict(globals(), **locals()))

try:
  while True:
    for emitter in EMITTERS:
      emitter.loop()
    time.sleep(1)
except KeyboardInterrupt:
  pass
