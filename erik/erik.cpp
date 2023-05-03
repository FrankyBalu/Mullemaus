/*
 * Erik
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
#include "raylib.h"
#include <mullemaus/core/log.hpp>
#include <mullemaus/core/mullemaus.hpp>
#include <mullemaus/core/mullemausOverlay.hpp>
#include <mullemaus/core/gamepad.hpp>
#include <mullemaus/core/keyboard.hpp>


//Erstmal nur zum testen

int main(int argc, char* argv[]) {
    bool fs = false;
    int posX = 0;
    int posY = 0;


    MM::Mullemaus::Instance()->Initialize("MM Demo: Erik", argc, argv);

    MM::Gamepad gamepad(0);
    MM::Keyboard keyboard;
    MM::MullemausOverlay overlay;
    overlay.AddText("Overlay test");
    overlay.SetTextColor(RED);
    overlay.SetTextSize(30);
    MM::Mullemaus::Instance()->changeOverlay(&overlay);

    while (MM::Mullemaus::Instance()->IsRunning()) {
        MM::Mullemaus::Instance()->HandleEvents();
        MM::Mullemaus::Instance()->Update();
        if (keyboard.KeyPressed(MM::KEY::ONE) ||
                gamepad.ButtonPressed(MM::GAMEPAD_BUTTON::RIGHT_FACE_DOWN)) {
            MM::Mullemaus::Instance()->changeOverlay(&overlay);
        }
        if (keyboard.KeyPressed(MM::KEY::F) ||
            gamepad.ButtonPressed(MM::GAMEPAD_BUTTON::RIGHT_FACE_LEFT)) {
            fs = !fs;
            MM::Mullemaus::Instance()->SetFullscreen(fs);
        }
        if (gamepad.AxisMovement(MM::GAMEPAD_AXIS::LEFT_X) < -0.01) {
            if (posX > 0)
                posX = posX - 10;
            overlay.SetPos(posX, posY);
        }
        if (gamepad.AxisMovement(MM::GAMEPAD_AXIS::LEFT_X) > 0.01) {
            if (posX < 700)
                posX = posX + 10;
            overlay.SetPos(posX, posY);
        }
        if (gamepad.AxisMovement(MM::GAMEPAD_AXIS::LEFT_Y) < -0.01) {
            if (posY > 0)
                posY = posY - 10;
            overlay.SetPos(posX, posY);
        }
        if (gamepad.AxisMovement(MM::GAMEPAD_AXIS::LEFT_Y) > 0.01) {
            if (posY < 500)
                posY = posY + 10;
            overlay.SetPos(posX, posY);
        }
        MM::Mullemaus::Instance()->Render();
    }
    MM::Mullemaus::Instance()->Clean();

    return 0;
}
