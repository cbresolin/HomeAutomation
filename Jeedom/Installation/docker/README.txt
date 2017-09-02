1) Download & flash raspian jessie lite on SD card (etcher)
2) Insert SD card into raspberry pi 3
3) Plug screen (HDMI) and keyboard to pi 3
4) Power on pi 3 and login (qwerty keyboard)
5) Enable SSH server using command
- sudo raspi-config
- go to menu to enable SSH server
6) Connect pi 3 to internet using RJ45 cable
7) Configure locales, keyboard, wifi , password using
- ssh pi@192.168.x.x + raspberry as password
- sudo raspi-config
8) Pair HC-05 or SPP-CA device to raspberry using:
- hcitool scan to get HC-05 BD address
- sudo bluetoothctl
-- pairable on
-- agent on
-- scan on
-- pair [BD address]
-- enter pin 1234
-- paired-devices to check
-- exit
9) Bind paired device to /dev/rfcomm0 using
- sudo rfcomm bind 0 [BD address]
- rfcomm to check
10) Add below to /etc/rc.local file so pi 3 create rfcomm device at system boot
- sudo rfcomm bind 0 [BD address]
11) Install docker using
- curl -sSL get.docker.com | sh
12) If you would like to use Docker as a non-root user, you should now consider
adding your user to the "docker" group with something like:
- sudo usermod -aG docker pi
Remember that you will have to log out and back in for this to take effect!
13) Allow docker to start automatically
- sudo systemctl enable docker
14) Install docker-compose on Raspberry Pi using
https://github.com/hypriot/arm-compose#installation
14) Reboot the system
- sudo reboot
15) Download & copy content of https://github.com/cbresolin/HomeAutomation/blob/master/Jeedom/Installation/docker to pi 3 in /home/pi path
16) Start Jeedom services using
- docker-compose up -d
This builds Jeedom service images according to docker-compose.yml file and starts all containers in detached mode)
17) If Jeedom images require to be rebuilt, use command
- docker-compose up -d --build --no-recreate
This rebuilds images without recreating containers if they already exist
18) Once containers are up, fill in localhost IP address and mysql database root password
- localhost IP address = jeedom-mysql IP address (docker inspect jeedom-mysql gives this address)
- mysql root password available in docker-compose.yml file
19) Jeedom finishes its installation
20) Once login with admin/admin, restore any relevant backup you have
21) OpenZwave dependancies will be installed automatically if zwave plugin is activated
