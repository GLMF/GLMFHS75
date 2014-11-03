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

  # lance la lecture en tâche de fond
  /usr/local/bin/play /usr/share/sounds/alsa/Front_Center.wav &

  # attend que la broche $1 retourne à 0 :
  until /bin/grep 0 /sys/class/gpio/gpio$1/value >> /dev/null
  do
    /bin/sleep .1 # libère le CPU
  done

  # interromp la lecture (si elle n'est pas terminée)
  /usr/bin/killall play
done