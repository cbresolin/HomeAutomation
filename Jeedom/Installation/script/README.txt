1) Download & flash raspian strech lite on SD card (etcher)
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
15) Download & copy content of https://github.com/cbresolin/HomeAutomation/blob/master/Jeedom/Installation/script to pi 3 in /home/pi path
16) Make script executable using
- chmod +x install.sh
17) Launch installation script using
- sudo ./install.sh -m Jeedom -v stable
18) Once login with admin/admin, restore any relevant backup you have
19) OpenZwave dependancies will be installed automatically if zwave plugin is activated
