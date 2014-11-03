[ -d /sys/class/gpio/gpio$1 ] ||
  echo $1 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio$1/direction

# boucle infinie
while true
do
  # attend que la broche $1 passe à 1 :
  until /bin/grep 1 /sys/class/gpio/gpio$1/value >> /dev/null
  do
    /bin/sleep .1 # libère le CPU
  done

  /usr/local/bin/play /usr/share/sounds/alsa/Front_Center.wav
done