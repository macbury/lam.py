# JenkinsLamp

Led lamp that displays information about current jenkins build status.

## Configuring device

Open `device/device.ino` in arduino ide. Copy `credentials.h.example` to `credentials.h`. Update it with your credentials and upload to Wemos D1.

## Running

Run python script

```
python3 src/lam.py
```

## Configuration of server

After cloning run:

```
pip3 install -r requirements.txt
```

Edit home configuration under `config.yaml` and after that run:

```
sudo cp systemd/lam.py.service /lib/systemd/system/
sudo systemctl enable lam.py
sudo systemctl start lam.py
```

## Free MQTT brokers

* https://github.com/mqtt/mqtt.github.io/wiki/public_brokers
* https://customer.cloudmqtt.com/login
