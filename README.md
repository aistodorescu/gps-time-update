## Description
This folder contains tools for setting up system date and time based on GPS raw
data reading. This is very useful when gps data is not good enough for ntp to 
automatically update system time.


## Building
You can build this program on any Unix system. The binary file set_date is build
for Raspberry PI(ARM architecture with floating point support).
gcc set_date.c -oset_date


## Find what device is mounted for your gps
If the device is a usb dongle then plug it in a USB port and call:
dmesg | grep tty
If the device is serial based, then you have to try
cat /dev/ttyAMA0
or
cat /dev/ttyS0
to see if you get some raw gps data and determine which one is mounted.

## How to use the tool
- start gpsd:
gpsd /dev/ttyAMA0
- start the updater script: 
./update_date.sh


## Customization
Edit the file update_date.sh and change the following options:
CURRENT_CENTURY - the curent century number
SLEEP_TIME - the number(in seconds) which sets how much time to pass between two 
clock updates


http://engineeringdiy.freeforums.org/<br>
www.engineering-diy.blogspot.com
