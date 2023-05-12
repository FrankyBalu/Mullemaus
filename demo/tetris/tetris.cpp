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

#include <mullemaus/core/filesystem.hpp>
#include <mullemaus/core/log.hpp>
#include <mullemaus/core/window.hpp>
#include <mullemaus/core/Utils.hpp>


int main(int argc, char* argv[]) {
    bool fs = false;
    int posX = 0;
    int posY = 0;

    MM::Filesystem::Init();
    MM::Filesystem::Mount("/home/frank", "/home");
    MM::Directory dir = MM::Filesystem::LoadDirectory("/home");

    for (int i = 0; i < dir.count; i++){
        LOG_INFO("{}", dir.entries[i]);
    }

    int count;
    MM::Window::Init(800, 600, "test fenster");

    MM::SetFPS(60);

    MM::Window::ClearBackground(100,200, 50, 255);

    while (!MM::Window::ShouldClose()){
        if (count > 240){
            MM::Window::SetTitle("neuer title");
        }
        if (count > 500){
          exit(0);
          }
        count++;
        MM::Window::BeginDrawing();
        MM::Window::EndDrawing();
    }

    return 0;
}
