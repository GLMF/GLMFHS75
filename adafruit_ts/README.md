# Écran SPI pour Raspberry Pi
par Pierre Ficheux [Directeur technique Open Wide Ingénierie]

---

La carte Raspberry Pi (RPi) fut initialement conçue comme un « PC bon marché ». Elle dispose donc d'un contrôleur graphique performant permettant la connexion à un écran HDMI externe. Dans cette configuration, il est possible d'utiliser un mode accéléré (OpenGL) compatible avec des bibliothèques graphiques telles que Qt 5. Cependant, de nombreuses applications embarquées utilisent un écran local (fixé à la carte) souvent tactile et permettant d'utiliser une application métier. Dans cet article, nous allons décrire la mise en place et l'utilisation sous Qt et DirectFB d'un écran 320x240 2,8 pouces, connecté au bus SPI de la carte RPi.
