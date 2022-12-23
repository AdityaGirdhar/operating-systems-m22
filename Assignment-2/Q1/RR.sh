#!/bin/bash

echo "Starting RR compilation..."
tar xvf linux-5.19.9.tar.xz -C ./RR/
cd ./RR/linux-5.19.9
make mrproper
wget https://raw.githubusercontent.com/adityagirdhar/test-repo/main/config-rev-9-gold
mv config-rev-9-gold .config
make
echo "Done"
cd ..
rm -r linux-5.19.9
echo "Files cleaned."
cd ..
exit
