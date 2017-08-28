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
9) Install docker-compose on Raspberry Pi using
https://github.com/hypriot/arm-compose#installation

Download url : https://github.com/jeedom/core/archive/releas.zip

16) inspect mysql docker to get its IP address so Jeedom can connect to it.
