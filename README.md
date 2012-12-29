UCS1903 (HTD-12IC LED)
==========

## Présentation
Le but de cette librairie est de commander des leds HTD-12IC via une carte arduino.

[Vidéo de démonstration](http://youtu.be/GfPRc44GJo4)

##Import de la librairie dans son projet arduino.
``` bash
# ajout d'un sous module dans du projet
git submodule add git@github.com:Pobot/Ucs1903.git projetArduino/libraries/Usc1903

# mise a jour du sous module
git submodule update
```

## Utilisation
Il est possible d'utiliser les leds sur n'importe qu'elle pin de donnée de l'arduino.
Le nombre max de led en serie est de 1000. Attention à l'alimentation des leds prévoir 3x18mA par led.
Pour le fonctionnement le plus simple est de regarder le fichier : demo/demo.ino

## Connection des leds
fil rouge : +5v
fil vert : data (attention d'utiliser l'entrée DI)
fil blanc : Gnd


## Licence
[![Contrat Creative Commons](http://i.creativecommons.org/l/by-nc/3.0/88x31.png)](http://creativecommons.org/licenses/by-nc/3.0/)

**UCS1903** de **Grégory Fromain** est mis à disposition selon les termes de la [licence Creative Commons Paternité - Pas d'Utilisation Commerciale 3.0 non transcrit](http://creativecommons.org/licenses/by-nc/3.0/).
Basé(e) sur une oeuvre à [github.com](https://github.com/greg06/Baba-Robot).