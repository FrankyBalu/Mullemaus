![ ](data/Logo.png)

﻿# MM

Mullemaus ist eine Engine zum erstellen von 2D spielen.


### Demos

Im zuge der Erstellung werden kleine Tutorial und Demos entstehen.

## Übersicht

Mullemaus dient als Lernprojekt zum erstellen eines 2D-Spiels und der dazugehörenden Engine.
Es soll möglichst einfach ein Spiel, mit wenig C++ und etwas lua entwickelt werden können.

# Bauanleitung

## Linux / BSD

Alle externen abhängigkeiten sind unter extra inegriert.

```
git clone https://github.com/FrankyBalu/Mullemaus.git
cd Mullemaus
mkdir build
cd build
cmake ..
make
sudo make install

```

## Windows

Es sollte mit jeder IDE gehen, die CMake unterstützt.


# Roadmap

## Version 0.0.1

- [X] [Logging Klasse]
- [X] [Fenstererstellen]
- [ ] [Schrift im Fenster darstellen]
- [ ] [Eingabe möglichkeiten]
- [ ] [Engine Objekte, um jeden Teil der Engine verfolgen zu können]
- [ ] [Renderer]
- [ ] [Texturen + Texturemanager]
## Version 0.0.2

- [ ] [Sprites]
- [ ] [Einstellungen mit lua laden]
- [ ] [GUI mit lua erstellen]

## Version 0.0.3

- [ ] [ Animationen]
- [ ] [Karten laden und Kamera implementieren]
- [ ] [Kollisionssystem]
- [ ] [Übergange zu den einzelnen Karten]
- [ ] [Wegweiser und Hinweisschilder]

## Version 0.0.4

- [ ] [NPCs]
- [ ] [Gegner]
- [ ] [Storyknoten]

## Version 0.0.5

- [ ] [Zerstörbares Gras und Gegenstände]
- [ ] [Inventar und Items]

## Future

- [ ] [KI für Gegner]

## Version 1.0.0

- [ ] [MM wird zu einem eigenständigen Projekt, ohne Erik]
- [ ] [Editor zum erstellen von Level]
