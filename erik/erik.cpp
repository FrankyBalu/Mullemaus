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
#include <mullemaus/core/overlaytext.hpp>
#include <mullemaus/core/gamepad.hpp>
#include <mullemaus/core/keyboard.hpp>


//Erstmal nur zum testen

int main(int argc, char* argv[]) {
    bool fs = false;
    int posX = 0;
    int posY = 0;


    MM::Mullemaus::Instance()->Initialize("Mullemaus Demo: Erik", argc, argv);

    MM::Gamepad gamepad(0);
    MM::Keyboard keyboard;
    MM::OverlayText overlay("Test");
    LOG_FATAL("overlay.name: {}", overlay.GetName());
    LOG_FATAL("overlay.class: {}", overlay.GetClass());
    LOG_FATAL("overlay.type: {}", overlay.GetType());
    LOG_FATAL("overlay.id: {}", overlay.GetID());


    overlay.AddText("Overlay test");
    overlay.SetTextColor(RED);
    overlay.SetTextSize(30);
    MM::Mullemaus::Instance()->AddTextOverlay(&overlay);

    while (MM::Mullemaus::Instance()->IsRunning()) {
        MM::Mullemaus::Instance()->HandleEvents();
        MM::Mullemaus::Instance()->Update();
        if (keyboard.KeyPressed(MM::KEY::F) ||
            gamepad.ButtonPressed(MM::GAMEPAD_BUTTON::RIGHT_FACE_LEFT)) {
            fs = !fs;
            MM::Mullemaus::Instance()->SetFullscreen(fs);
        }
        if (keyboard.KeyPressed(MM::KEY::LEFT) ||
        gamepad.AxisMovement(MM::GAMEPAD_AXIS::LEFT_X) < -0.01) {
            if (posX > 0)
                posX = posX - 10;
            overlay.SetPos(posX, posY);
        }
        if (keyboard.KeyPressed(MM::KEY::RIGHT) ||
        gamepad.AxisMovement(MM::GAMEPAD_AXIS::LEFT_X) > 0.01) {
            if (posX < 700)
                posX = posX + 10;
            overlay.SetPos(posX, posY);
        }
        if (keyboard.KeyPressed(MM::KEY::UP) ||
        gamepad.AxisMovement(MM::GAMEPAD_AXIS::LEFT_Y) < -0.01) {
            if (posY > 0)
                posY = posY - 10;
            overlay.SetPos(posX, posY);
        }
        if (keyboard.KeyPressed(MM::KEY::DOWN) ||
        gamepad.AxisMovement(MM::GAMEPAD_AXIS::LEFT_Y) > 0.01) {
            if (posY < 500)
                posY = posY + 10;
            overlay.SetPos(posX, posY);
        }
        MM::Mullemaus::Instance()->Render();
    }
    MM::Mullemaus::Instance()->Clean();

    return 0;
}
