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

#ifndef MULLEMAUS_RENDERER_HPP
#define MULLEMAUS_RENDERER_HPP

#include "../core/mullemaus_api.hpp"
#include "color.hpp"

namespace MM {
    extern "C" {

    MULLEMAUS_API class Renderer {
    public:
        Renderer();
        static void BeginDrawing();
        static void EndDrawing();

        static void DrawRect (int left, int up, int width, int height, const Color col);
        static void DrawLine (int startPosX, int startPosY, int endPosX, int endPosY, const Color color);

    };
    }//extern C
}//namespace MM

#endif //MULLEMAUS_RENDERER_HPP
