import jenkins

class Status():
  def __init__(self, config):
    self.jobs = config['jobs']
    self.client = jenkins.Jenkins(
      url=config['url'],
      username=config['user'],
      password=config['password']
    )

  def is_observed(self, other_job_name):
    for job_name in self.jobs:
      if other_job_name.startswith(job_name):
        return True
    return False

  def color_to_status(self, color):
    if color == "blue":
      return "success"
    elif color == "red":
      return "failed"
    elif color == "yellow":
      return "unstable"
    elif color == "grey" or color == "notbuilt":
      return "not_run"
    elif color == "aborted":
      return "aborted"
    elif color == "disabled":
      return "disabled"
    else:
      return "running"

  def list_by_status(self):
    projects = {}
    for job in self.client.get_all_jobs():
      if self.is_observed(job['name']):
        status = self.color_to_status(job['color'])
        if not status in projects:
          projects[status] = []
        projects[status].append(job['name'])
    return projects

  def status(self):
    statuses = self.list_by_status()
    if 'running' in statuses:
      return 'running'
    if 'failed' in statuses:
      return 'failed'
    if 'success' in statuses:
      return 'success'
    return 'wtf'
