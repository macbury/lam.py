# JenkinsLamp
Simple lamp app

## Running

Run python script

```
python3 src/lam.py
```

## Configuration

After cloning run:

```
pip3 install -r requirements.txt
```

Edit home configuration under `$USER/.config/jenkins_lamp.yaml` and after that run:

```
sudo cp systemd/lam.py.service /lib/systemd/system/
sudo systemctl enable lam.py
sudo systemctl start lam.py
```

## Free MQTT brokers

* https://github.com/mqtt/mqtt.github.io/wiki/public_brokers
* https://customer.cloudmqtt.com/login

https://github.com/RidersDiscountCom/HypChat/blob/master/TYPES.rst
