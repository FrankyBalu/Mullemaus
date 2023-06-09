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

#include "../../include/mullemaus/render/renderer.hpp"
#include <raylib.h>
#include "../../include/mullemaus/core/log.hpp"

MM::Renderer::Renderer() {

}

void MM::Renderer::BeginDrawing() {
    ::BeginDrawing();
}

void MM::Renderer::EndDrawing() {
    ::EndDrawing();
}

void MM::Renderer::DrawRect(int left, int up, int width, int height, MM::Color col) {
    ::DrawRectangle(left, up, width, height, {col.r, col.g, col.b,col.a});
}

void MM::Renderer::DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, const MM::Color color) {
    ::DrawLine(startPosX, startPosY, endPosX, endPosY, {color.r, color.g, color.b, color.a});
}