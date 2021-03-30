#!/bin/bash 

# userspace permissions for uio
sudo bash -c 'echo "KERNEL==\"uio[0-9]*\", GROUP=\"root\", MODE=\"0666\"" > /etc/udev/rules.d/99-uio.rules'

#reload udev rules
#https://unix.stackexchange.com/questions/39370/how-to-reload-udev-rules-without-reboot
sudo bash -c 'udevadm control --reload-rules && udevadm trigger'
