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
11) Reboot the system
- sudo reboot
12) Download & copy content of https://github.com/cbresolin/HomeAutomation/blob/master/Jeedom/Installation/script to pi 3 in /home/pi path
13) Make script executable using
- chmod +x install.sh
14) Launch installation script using
- sudo bash ./install.sh -m Jeedom -v stable
15) Once login with admin/admin, restore any relevant backup you have
16) OpenZwave dependancies will be installed automatically if zwave plugin is activated
