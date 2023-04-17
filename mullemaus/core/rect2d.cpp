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

#include "rect2d.hpp"
#include <raylib.h>

MM::Rect2D::Rect2D() :pX(0),pY(0),pWidth(0),pHeight(0){
}

MM::Rect2D::Rect2D(float x, float y, float width, float height) :pX(x),pY(y),pWidth(width),pHeight(height){
}

void MM::Rect2D::SetX(float x) {
    pX = x;
}

float MM::Rect2D::GetX() {
    return pX;
}

void MM::Rect2D::SetY(float y) {
    pY = y;
}

float MM::Rect2D::GetY() {
    return pY;
}

void MM::Rect2D::SetWidth(float width) {
    pWidth = width;
}

float MM::Rect2D::GetWidth() {
    return pWidth;
}

void MM::Rect2D::SetHeight(float height) {
    pHeight = height;
}

float MM::Rect2D::GetHeight() {
    return pHeight;
}

void MM::Rect2D::SetPos(float x, float y) {
    pX = x;
    pY = y;
}

void MM::Rect2D::SetSize(float width, float height) {
    pWidth = width;
    pHeight = height;
}

Rectangle* MM::Rect2D::GetRectangle() {
    Rectangle *rect = new Rectangle;
    rect->x = pX;
    rect->y = pY;
    rect->width = pWidth;
    rect->height = pHeight;
    return rect;
}