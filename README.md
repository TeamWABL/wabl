# wabl
Wheeled Autonomous Balancing Limb - Inverted Pendulum Controller

[WABL Project Page](http://teamwabl.github.io/wabl)

# notes
Note for Orangutan SVP and X2 users: AVRDUDE has incorrect chip erase delay settings for the ATmega324P, ATmega644P, ATmega1284P. This means that when you try to program, the erase operation will take longer than AVRDUDE expects and AVRDUDE will interpret this as an error. The workaround is to find the AVRDUDE configuration file, avrdude.conf, and increase the chip erase delay for the m324p/m644p/m1284p to 55000. The file is located in /etc/ in Linux.
