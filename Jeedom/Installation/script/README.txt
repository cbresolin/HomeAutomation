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
- sudo bash ./install.sh -m Jeedom
15) Once login with admin/admin, restore any relevant backup you have
16) OpenZwave dependancies will be installed automatically if zwave plugin is activated
17) To activate listening on port 443 (SSL), follow https://certbot.eff.org/lets-encrypt/debianbuster-apache and select apache for debian 10 (Burst)
- Make sure to temporarily enable Box redirection on port 80 to 80 as requested, otherwise generation of certificates won't be working

- Ouptut when it works:
Saving debug log to /var/log/letsencrypt/letsencrypt.log
Plugins selected: Authenticator apache, Installer apache
No names were found in your configuration files. Please enter in your domain
name(s) (comma and/or space separated)  (Enter 'c' to cancel): jeedom.cbresolin.ovh
Requesting a certificate for jeedom.cbresolin.ovh
Performing the following challenges:
http-01 challenge for jeedom.cbresolin.ovh
Enabled Apache rewrite module
Waiting for verification...
Cleaning up challenges
Created an SSL vhost at /etc/apache2/sites-available/000-default-le-ssl.conf
Enabled Apache socache_shmcb module
Enabled Apache ssl module
Deploying Certificate to VirtualHost /etc/apache2/sites-available/000-default-le-ssl.conf
Enabling available site: /etc/apache2/sites-available/000-default-le-ssl.conf
Enabled Apache rewrite module
Redirecting vhost in /etc/apache2/sites-enabled/000-default.conf to ssl vhost in /etc/apache2/sites-available/000-default-le-ssl.conf

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Congratulations! You have successfully enabled https://jeedom.cbresolin.ovh
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IMPORTANT NOTES:
 - Congratulations! Your certificate and chain have been saved at:
   /etc/letsencrypt/live/jeedom.cbresolin.ovh/fullchain.pem
   Your key file has been saved at:
   /etc/letsencrypt/live/jeedom.cbresolin.ovh/privkey.pem
   Your certificate will expire on 2021-07-28. To obtain a new or
   tweaked version of this certificate in the future, simply run
   certbot again with the "certonly" option. To non-interactively
   renew *all* of your certificates, run "certbot renew"

21) To restart hciuart service if no default BT controller is present
- sudo systemctl start hciuart -l
22) To re-install BT on pi:
- sudo apt-get purge pi-bluetooth raspberrypi-sys-mods
- sudo apt-get install pi-bluetooth raspberrypi-sys-mods
- sudo reboot
