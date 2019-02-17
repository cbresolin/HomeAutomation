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
17) To activate listening on port 443 (SSL), follow https://www.wistee.fr/installer-ssl/apache2-mod-ssl.html
18) Create a folder in /etc/apache2/ssl
19) Create your private/public keys and store them in /etc/apache2/ssl
- sudo mkdir -p /etc/apache2/ssl
- sudo openssl req -x509 -nodes -days 3650 -newkey rsa:4096 -keyout /etc/apache2/ssl/apache2.key -out /etc/apache2/ssl/apache2.crt -subj "/C=FR/ST=France/L=Toulouse/O=./OU=./CN=jeedom.cbresolin.ovh/emailAddress=christophe.bresolin@gmail.com"
- sudo chmod 400 /etc/apache2/ssl/apache2.key
20) Make apache2 points to your certs
- sudo nano /etc/apache2/sites-available/default-ssl.conf
21) To restart hciuart service if no default BT controller is present
- sudo systemctl start hciuart -l
22) To re-install BT on pi:
- sudo apt-get purge pi-bluetooth raspberrypi-sys-mods
- sudo apt-get install pi-bluetooth raspberrypi-sys-mods
- sudo reboot
