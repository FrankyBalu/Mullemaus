/*
 * Kleinod
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
#include <mullemaus/core/MullemausOverlay.hpp>
#include <mullemaus/core/gamepad.hpp>
#include <mullemaus/core/keyboard.hpp>


//Erstmal nur zum testen

int main(int argc, char* argv[]) {


    MM::Mullemaus::Instance()->Initialize("Mullemaus Demo: Kleinod", argc, argv);

    while (MM::Mullemaus::Instance()->IsRunning()) {
        MM::Mullemaus::Instance()->HandleEvents();
        MM::Mullemaus::Instance()->Update();
        MM::Mullemaus::Instance()->Render();
    }
    MM::Mullemaus::Instance()->Clean();

    return 0;
}
