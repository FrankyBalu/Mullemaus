/*
 * Mullemaus
 * Copyright (C) 2023   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "keyboard.hpp"
#include <raylib.h>
#include <map>


std::map<int,std::string> keymap{{0,"NULL"},
                                 {39, "\'"},
                                 {44, ","},
                                 {45, "-"},
                                 {46, "."},
                                 {47, "/"},
                                 {48, "0"},
                                 {49, "1"},
                                 {50, "2"},
                                 {51, "3"},
                                 {52, "4"},
                                 {53, "5"},
                                 {54, "6"},
                                 {55, "7"},
                                 {56, "8"},
                                 {57, "9"},
                                 {59, ";"},
                                 {61, "="},
                                 {65, "A"},
                                 {66, "B"},
                                 {67, "C"},
                                 {68, "D"},
                                 {69, "E"},
                                 {70, "F"},
                                 {71, "G"},
                                 {72, "H"},
                                 {73, "I"},
                                 {74, "J"},
                                 {75, "K"},
                                 {76, "L"},
                                 {77, "M"},
                                 {78, "N"},
                                 {79, "O"},
                                 {80, "P"},
                                 {81, "Q"},
                                 {82, "R"},
                                 {83, "S"},
                                 {84, "T"},
                                 {85, "U"},
                                 {86, "V"},
                                 {87, "W"},
                                 {88, "X"},
                                 {89, "Y"},
                                 {90, "Z"},
                                 {91, "["},
                                 {92, "\\"},
                                 {93, "]"},
                                 {96, "`"},
                                 {32, "SPACE"},
                                 {256, "ESC"},
                                 {257, "ENTER"},
                                 {258, "TAB"},
                                 {259, "BACKSPACE"},
                                 {260, "Ins"},
                                 {261, "Del"},
                                 {262, "CURSOR RIGHT"},
                                 {263, "CURSOR LEFT"},
                                 {264, "CURSOR DOWN"},
                                 {265, "CURSOR UP"},
                                 {266, "PAGE UP"},
                                 {267, "PAGE DOWN"},
                                 {268, "HOME"},
                                 {269, "END"},
                                 {280, "CAPS  LOCK"},
                                 {281, "SCROLL DOWN"},
                                 {282, "NUM LOCK"},
                                 {283, "PRINT"},
                                 {284, "PAUSE"},
                                 {290, "F1"},
                                 {291, "F2"},
                                 {292, "F3"},
                                 {293, "F4"},
                                 {294, "F5"},
                                 {295, "F6"},
                                 {296, "F7"},
                                 {297, "F8"},
                                 {298, "F9"},
                                 {299, "F10"},
                                 {300, "F11"},
                                 {301, "F12"},
                                 {340, "SHIFT LEFT"},
                                 {341, "CONTROL LEFT"},
                                 {342, "ALT LEFT"},
                                 {343, "SUPER LEFT"},
                                 {344, "SHIFT RIGHT"},
                                 {345, "CONTROL RIGHT"},
                                 {346, "ALT RIGHT"},
                                 {347, "SUPER RIGHT"},
                                 {348, "KB MENU"},
                                 {320, "KP 0"},
                                 {321, "KP 1"},
                                 {322, "KP 2"},
                                 {323, "KP 3"},
                                 {324, "KP 4"},
                                 {325, "KP 5"},
                                 {326, "KP 6"},
                                 {327, "KP 7"},
                                 {328, "KP 8"},
                                 {329, "KP 9"},
                                 {330, "KP ."},
                                 {331, "KP /"},
                                 {332, "KP *"},
                                 {333, "KP -"},
                                 {334, "KP +"},
                                 {335, "KP ENTER"},
                                 {336, "KP ="}};











MM::Keyboard::Keyboard() {

}

void MM::Keyboard::ExitKey(MM::KEY key) {
    SetExitKey(static_cast<int>(key));
}

std::string MM::Keyboard::KeyName(MM::KEY key) {
    return keymap[static_cast<int>(key)];
}

bool MM::Keyboard::KeyUp(MM::KEY key) {
    return IsKeyUp(static_cast<int>(key));
}

bool MM::Keyboard::KeyDown(MM::KEY key) {
    return IsKeyDown(static_cast<int>(key));
}

bool MM::Keyboard::KeyReleased(MM::KEY key) {
    return IsKeyReleased(static_cast<int>(key));
}

bool MM::Keyboard::KeyPressed(MM::KEY key) {
    return IsKeyPressed(static_cast<int>(key));
}