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

#include "gamepad.hpp"
#include <raylib.h>

MM::Gamepad::Gamepad(int pad) :pPadNumber(pad){}

bool MM::Gamepad::ButtonPressed(MM::GAMEPAD_BUTTON button) {
    return IsGamepadButtonPressed(pPadNumber, static_cast<int>(button));
}

bool MM::Gamepad::ButtonReleased(MM::GAMEPAD_BUTTON button) {
    return IsGamepadButtonReleased(pPadNumber, static_cast<int>(button));
}

bool MM::Gamepad::ButtonDown(MM::GAMEPAD_BUTTON button) {
    return IsGamepadButtonDown(pPadNumber, static_cast<int>(button));
}

bool MM::Gamepad::ButtonUp(MM::GAMEPAD_BUTTON button) {
    return IsGamepadButtonUp(pPadNumber, static_cast<int>(button));
}

int MM::Gamepad::AxisCount() {
    return GetGamepadAxisCount(pPadNumber);
}

float MM::Gamepad::AxisMovement(MM::GAMEPAD_AXIS axis) {
    return GetGamepadAxisMovement(pPadNumber, static_cast<int>(axis));
}