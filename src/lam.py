import logging
import os
import time
from hipchat import Hipchat
from status import Status
from mqtt import MqttClient, EmitPresence, EmitStatus

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

emit_status = EmitStatus(mqtt_client, jenkins_status, CONFIG['topics']['jenkins_status'])
emit_presence = EmitPresence(mqtt_client, hipchat, CONFIG['topics']['presence'])
#button_handler = ButtonHandler(mqtt_client, CONFIG['topics']['button'])

try:
  while True:
    emit_status.loop()
    emit_presence.loop()
    time.sleep(1)
except KeyboardInterrupt:
  pass
