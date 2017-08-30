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
8) Pair HC-05 device to raspberry using:
- hcitool scan to get HC-05 BD address
- sudo bluetoothctl
-- pairable on
-- agent on
-- scan on
-- pair 98:D3:31:FC:1E:28
-- enter pin 1234
-- paired-devices to check
-- exit
9) Bind paired device to /dev/rfcomm0 using
- sudo rfcomm bind 0 98:D3:31:FC:1E:28
- rfcomm to check
10) Add below to /etc/rc.local file so pi 3 create rfcomm device at system boot
- sudo rfcomm bind 0 98:D3:31:FC:1E:28
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
15) Login to docker hub (cbresolin) while repos are private (no need when public) using
- docker login
15) Download & copy docker-compose-jeedom-install.yml file to pi 3 (/home/pi)
https://github.com/cbresolin/HomeAutomation/blob/master/Jeedom/Installation/docker
16) Pull Jeedom docker images and start Jeedom services using
- docker-compose -f docker-compose-jeedom-install.yml up -d





16) inspect mysql docker to get its IP address so Jeedom can connect to it.
