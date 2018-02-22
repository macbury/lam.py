from hypchat import HypChat

class Hipchat(object):
  def __init__(self, config):
    self.config = config
    self.client = HypChat(config['token'])
    self.team = config['team']
    self.sendToUser = config['mode'] != 'room'

  def message(self, user, body):
    if self.sendToUser:
      self.client.get_user(user).message(body)
    else:
      self.client.get_room(user).message(body)

  def is_anybody_online(self):
    for member in self.team:
      presence = self.client.get_user(member)['presence']

      if presence is not None and \
        presence['client']['type'] == 'http://hipchat.com/client/mac/macweb' and \
        presence['is_online']:
        return True
    return False
