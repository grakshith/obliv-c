#! /bin/bash

echo "Network before"
a=$(cat /proc/net/dev | grep "lo:" | cut -d " " -f6)
echo $a

./a.out 1234 -- `python2 -c "print 'a'*1500"` &
sleep 1
./a.out 1234 localhost `python2 -c "print 'a'*1500"`

echo "Network after"
b=$(cat /proc/net/dev | grep "lo:" | cut -d " " -f6)
echo "GC Network cost in bytes"
c=$(($b-$a))
echo $c



