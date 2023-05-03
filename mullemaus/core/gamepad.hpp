/*
 * MM
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

#ifndef ERIK_GAMEPAD_HPP
#define ERIK_GAMEPAD_HPP

namespace MM {

    enum class GAMEPAD_BUTTON {
        UNKNOWN = 0,         // Unknown button, just for error checking
        LEFT_FACE_UP,        // Gamepad left DPAD up button
        LEFT_FACE_RIGHT,     // Gamepad left DPAD right button
        LEFT_FACE_DOWN,      // Gamepad left DPAD down button
        LEFT_FACE_LEFT,      // Gamepad left DPAD left button
        RIGHT_FACE_UP,       // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
        RIGHT_FACE_RIGHT,    // Gamepad right button right (i.e. PS3: Square, Xbox: X)
        RIGHT_FACE_DOWN,     // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
        RIGHT_FACE_LEFT,     // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
        LEFT_TRIGGER_1,      // Gamepad top/back trigger left (first), it could be a trailing button
        LEFT_TRIGGER_2,      // Gamepad top/back trigger left (second), it could be a trailing button
        RIGHT_TRIGGER_1,     // Gamepad top/back trigger right (one), it could be a trailing button
        RIGHT_TRIGGER_2,     // Gamepad top/back trigger right (second), it could be a trailing button
        MIDDLE_LEFT,         // Gamepad center buttons, left one (i.e. PS3: Select)
        MIDDLE,              // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
        MIDDLE_RIGHT,        // Gamepad center buttons, right one (i.e. PS3: Start)
        LEFT_THUMB,          // Gamepad joystick pressed button left
        RIGHT_THUMB          // Gamepad joystick pressed button right
    };

// Gamepad axis
    enum class GAMEPAD_AXIS {
        LEFT_X = 0,     // Gamepad left stick X axis
        LEFT_Y = 1,     // Gamepad left stick Y axis
        RIGHT_X = 2,     // Gamepad right stick X axis
        RIGHT_Y = 3,     // Gamepad right stick Y axis
        LEFT_TRIGGER = 4,     // Gamepad back trigger left, pressure level: [1..-1]
        RIGHT_TRIGGER = 5      // Gamepad back trigger right, pressure level: [1..-1]
    };

    class Gamepad {
    public:
        Gamepad(int pad);
        bool Avaible ();

        bool ButtonPressed(GAMEPAD_BUTTON button);

        bool ButtonReleased(GAMEPAD_BUTTON button);

        bool ButtonDown(GAMEPAD_BUTTON button);

        bool ButtonUp(GAMEPAD_BUTTON button);

        int AxisCount();

        float AxisMovement(GAMEPAD_AXIS axis);

    private:
        int pPadNumber;
    };

} // MM

#endif //ERIK_GAMEPAD_HPP
