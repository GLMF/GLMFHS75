#!/bin/bash

GPIO_IN=/sys/class/gpio/gpio7/value
SON_ON=/usr/share/sounds/alsa/Front_Center.wav
SON_OFF=/usr/share/sounds/alsa/Front_Left.wav

[ -d /sys/class/gpio/gpio7 ] ||
  echo 7 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio7/direction

function playwhile() {
  # $1 : état à tester
  # $2 : fichier à lire
  [[ $1 == "$(< $GPIO_IN)" ]] || /usr/local/bin/play -q $2 &

  while [[ "$(jobs)" ]]
  do
    jobs > /dev/null
    [[ $1 == "$(< $GPIO_IN)" ]] && /usr/bin/killall /usr/local/bin/play >> /dev/null 2>&1
    /bin/sleep .1
  done
}

while true
do
  playwhile 0 $SON_ON
  playwhile 1 $SON_OFF
done