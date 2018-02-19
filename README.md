# JenkinsLamp
Simple lamp app

## Configuration
Edit home configuration under `$USER/.config/jenkins_lamp.yaml` and after that run:

```
sudo cp systemd/jenkins-lamp.service /lib/systemd/system/
sudo systemctl enable jenkins-lamp
sudo systemctl start jenkins-lamp
```

https://github.com/mqtt/mqtt.github.io/wiki/public_brokers
