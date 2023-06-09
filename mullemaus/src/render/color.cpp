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

#include "../../include/mullemaus/render/color.hpp"
#include <raylib.h>
#include "../../include/mullemaus/core/log.hpp"

MM::Color::Color() {
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}

/*MM::Color::Color(MM::Color color) {
    this->a = color.a;
    this->g = color.g;
    this->b = color.b;
    this->a = color.a;
}*/

MM::Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
    this->r = red;
    this->g = green;
    this->b = blue;
    this->a = alpha;

}

void MM::Color::Fade(float alpha) {
    ::Color tempColor = ::Fade({r,g,b,a}, alpha);
    r = tempColor.r;
    g = tempColor.g;
    b = tempColor.b;
    a = tempColor.a;
}

int MM::Color::ToInt() {
    return ColorToInt({r,g,b,a});
}

void MM::Color::Tint(MM::Color Tint) {
    ::Color tempColor = ::ColorTint({r,g,b,a}, {Tint.r,Tint.g,Tint.b,Tint.a});
    r = tempColor.r;
    g = tempColor.g;
    b = tempColor.b;
    a = tempColor.a;
}