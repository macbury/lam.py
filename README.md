# JenkinsLamp

Led lamp that displays information about current jenkins build status. Main features:

* Automaticaly turn on/off if user is logged on hipchat
* Beam effect if somebody makes coffee
* Unicorn effect if food is delivered(via. lunching.pl)
* Big red arcade button that can send random message to somebody on hipchat
* Change color depending on jenkins build status

## Failing builds
![](doc/failing.gif)

## Running builds
![](doc/running.gif)

## Success builds
![](doc/success.gif)

## Wiring
![](doc/sketch.png)

## Requirements

* (IKEA Jar EKLATANT)[http://www.ikea.com/pl/pl/catalog/products/10376601/]
* Arcade button(everything is better with arcade button)
* Wemos D1 mini
* NeoPixel 5V LED RGB WS2812B strip
* Wires(of curse,)
* Toilet paper inner tube
* 4 amp power source
* Frozen glass spray

## Preparing device

### Make hole in the lid of the jar and put arcade button
![](doc/step1.jpg)
### Apply frozen glass effect to glass jar(3 coatings min.)
![](doc/step2.jpg)
### Wrap the tube using led strip and connect elements
![](doc/step3.jpg)

### Upload code to Wemos D1 mini

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
