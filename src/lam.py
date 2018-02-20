import logging
import os
import time
from hipchat import Hipchat
from status import Status
from mqtt import MqttClient, EmitStatus, ButtonHandler

from ruamel.yaml import YAML

LOGGER = logging.getLogger('lamp')
logging.basicConfig(
  level=logging.INFO,
  format="[%(asctime)s] %(levelname)s:%(name)s:%(message)s"
)

CONFIG_PATH = os.path.join('./', 'config.yaml')
LOGGER.info("Loading config: " + CONFIG_PATH)
CONFIG = YAML(typ='safe').load(open(CONFIG_PATH))

jenkins_status = Status(CONFIG['jenkins'])
hipchat = Hipchat(CONFIG['hipchat'])
mqtt_client = MqttClient(CONFIG['mqtt'])

emit_status = EmitStatus(mqtt_client, CONFIG['topics']['jenkins_status'])
button_handler = ButtonHandler(mqtt_client, CONFIG['topics']['button'])

try:
  while True:
    status = jenkins_status.get()
    LOGGER.info("Current status: {}".format(status))
    emit_status.run(status)
    time.sleep(1)
except KeyboardInterrupt:
  pass
