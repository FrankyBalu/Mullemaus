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

#ifndef MULLEMAUS_RECT2D_HPP
#define MULLEMAUS_RECT2D_HPP

#include "mullemaus_api.hpp"

typedef struct Rectangle Rectangle;

namespace MM {

    extern "C" {
    MULLEMAUS_API class Rect2D {
    public:
        Rect2D();
        Rect2D(float x, float y, float width, float height);

        void SetX(float x);
        float GetX();

        void SetY(float y);
        float GetY();

        void SetWidth(float width);
        float GetWidth();

        void SetHeight(float height);
        float GetHeight();

        void SetPos(float x, float y);
        void SetSize(float width, float height);

        Rectangle* GetRectangle ();

    private:
        float pX;
        float pY;
        float pWidth;
        float pHeight;
    };
    }
} // MM

#endif //MULLEMAUS_RECT2D_HPP
