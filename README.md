# Mullemaus

Framework bzw. Engine zum erstellen von 2d Spielen in c++.

### Erik

Jump and Run das als Demo für Mullemaus dient.

### Kleinod

RPG Demo für Mullemaus.

## Übersicht

Mullemaus dient als Lernprojekt zum erstellen eines 2D-Spiels und der dazugehörenden Engine.
Es soll möglichst einfach ein Spiel, mit wenig C++ und etwas lua entwickelt werden können.

# Bauanleitung

## Linux / BSD

Es werden tinyxml2-dev, zlib-dev, lua-dev, physfs-dev und spdlog-dev zum bauen benötigt.

```
git clone https://github.com/FrankyBalu/Erik.git
cd Erik
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
- [X] [Schrift im Fenster darstellen]
- [ ] [Eingabe möglichkeiten]
- [ ] [Engine Objekte, um jeden Teil der Engine verfolgen zu können]

## Version 0.0.2

- [ ] [Renderer]
- [ ] [Texturen]
- [ ] [Sprites]
- [ ] [Einstellungen mit lua laden]
- [ ] [Menüs mit lua erstellen]

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

- [ ] [Mullemaus wird zu einem eigenständigen Projekt, ohne Erik]
- [ ] [Editor zum erstellen von Level]
