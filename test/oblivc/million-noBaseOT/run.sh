#! /bin/bash

echo "Network before"
a=$(cat /proc/net/dev | grep "lo:" | cut -d " " -f6)
echo $a

./a.out 1234 -- 5000 &
sleep 1
./a.out 1234 localhost 10000

echo "Network after"
b=$(cat /proc/net/dev | grep "lo:" | cut -d " " -f6)
echo "GC Network cost in bytes"
c=$(($b-$a))
echo $c



