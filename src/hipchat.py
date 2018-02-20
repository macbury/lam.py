from hypchat import HypChat

class Hipchat(object):
  def __init__(self, config):
    self.config = config
    self.client = HypChat(config['token'])
    self.team = config['team']

  def is_anybody_online(self):
    for member in self.team:
      presence = self.client.get_user(member)['presence']
      #import code; code.interact(local=dict(globals(), **locals()))
      if presence is not None and \
        presence['client']['type'] == 'http://hipchat.com/client/mac/macweb' and \
        presence['is_online']:
        return True
    return False
