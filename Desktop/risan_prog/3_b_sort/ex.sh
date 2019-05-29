#!/bin/sh

tar zxvf kadai56.tar.gz
honest_c=`cat /dev/urandom | tr -dc '1-9' | fold -w 5 | head -n1 | tr "\n" "0"`
sed -i -e "s/C_HONEST/$honest_c/g" ./kadai56/*.c
sed -i -e "s/C_HONEST/$honest_c/g" ./kadai56/*.h

