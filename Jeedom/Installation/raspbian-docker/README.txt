1) Download & flash raspian jessie lite on SD card (etcher)
2) Insert SD card into raspberry pi 3
3) Configure locales, keyboard, wifi & enable ssh server using
- sudo raspi-config
4) Connect raspberry pi to internet using RJ45 connector
5) Pair HC-05 device to raspberry using:
- hcitool scan to get HC-05 BD address
- sudo bluetoothctl
-- pairable on
-- agent on
-- scan on
-- pair 98:D3:31:FC:1E:28
-- enter pin
-- paired-devices to check
-- exit
5) Bind paired device to /dev/rfcomm0 using (add it to /etc/rc.local file)
- sudo rfcomm bind 0 98:D3:31:FC:1E:28
- rfcomm to check
6) Install docker using
- curl -sSL get.docker.com | sh
or
- apt-get update
- apt-get install docker
- apt-get install docker.io
7) Allow docker to start automatically
- sudo systemctl enable docker
8) Reboot the system
- sudo reboot
9) Follow instructions from https://hub.docker.com/r/sbeuzit/rpi-jeedom/ &
https://diyprojects.io/docker-easily-test-home-automation-software-raspberry-pi/#.WU9uxmTiLPs

- sudo docker run --name jeedom-data \
                  sbeuzit/rpi-jeedom-data

- sudo docker run --name jeedom-mysql \
                  --volumes-from jeedom-data \
                  -e MYSQL_ROOT_PASSWORD=mysqlroot \
                  --restart=always \
                  -d hypriot/rpi-mysql

- sudo docker run --name jeedom-oz \
                  --link jeedom-mysql:mysql \
                  --device=/dev/ttyACM0:/dev/ttyACM0 \
                  --device=/dev/rfcomm0:/dev/rfcomm0 \
                  -p 80:80 -p 8083:8083 -p 443:443 \
                  --restart=always \
                  -d sbeuzit/rpi-jeedom-oz

- sudo docker run --name jeedom-test \
                --link jeedom-mysql-ref:mysql \
                --device=/dev/ttyACM0:/dev/ttyACM0 \
                --device=/dev/rfcomm0:/dev/rfcomm0 \
                -p 80:80 -p 8083:8083 -p 443:443 \
                --restart=always \
                -d cbresoli/jeedom-test

                  --mac-address="02:42:1a:4a:5b:66" \

10) Upload Jeedom backups version 2.4.6 & restore it
11) Relaunch zwave dependancies installation in zwave plugin
- select /dev/ttyACM0 for zwave controller
12) Once zwave demon is OK, restore zwave configuration
13) Check new versions, and upgrade to 3.0.x if required
14) Change ownership to www-data into jeedom-oz container
using
- docker exec -ti jeedom-oz bash
-- sudo chown www-data:www-data /var/www/html
-- sudo usermod -a -G dialout,tty www-data

15) Install docker-compose on Raspberry Pi using
https://github.com/hypriot/arm-compose#installation


Download url : https://github.com/jeedom/core/archive/stablev3.zip

# To build from docker compose yaml file
docker-compose build --force-rm --no-cache jeedom

# To build reference image for jeedom
docker build --no-cache --rm --tag cbresoli/jeedom-test:latest .
