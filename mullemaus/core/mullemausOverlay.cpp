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

#include "mullemausOverlay.hpp"
#include "mullemaus.hpp"
#include "log.hpp"
#include "raylib.h"
#include <sstream>


MM::MullemausOverlay::MullemausOverlay()
        : pMsg(), pNumLines(0), pTextSize(MM::Mullemaus::Instance()->GetDefaultFontSize()), pPosX(0), pPosY(0),
          pTextColor(BLACK) {
    pPosY += MM::Mullemaus::Instance()->GetDefaultFontSize();
    pName = "Overlay_";
    pName += std::to_string(GetRandomValue(1, 32767));
    LOG_DEBUG("Create a new Overlay: {}", pName);
}


void MM::MullemausOverlay::AddText(const std::string msg) {
    auto ss = std::stringstream{msg};

    for (std::string line; std::getline(ss, line, '\n');) {
        pMsg[pNumLines] = line;
        pNumLines++;
    }
}

void MM::MullemausOverlay::RemoveText(long unsigned int line) {
    line--;
    if (line > pMsg.size()) {
        LOG_ERROR("Line {} do not exist!", line);
        return;
    }
    auto iter = pMsg.find(line);
    if (iter != pMsg.end())
        pMsg.erase(iter);
}

void MM::MullemausOverlay::SetTextSize(int size) {
    LOG_DEBUG("Overlay {} set text size to {}", pName, size);
    pTextSize = size;
}

void MM::MullemausOverlay::SetTextColor(Color color) {
    LOG_DEBUG("Overlay {} set text size to R:{} G:{} B{}", pName, color.r, color.g, color.b);
    pTextColor = color;
}

void MM::MullemausOverlay::Render() {
    if (!IsFontReady((*Mullemaus::Instance()->GetDefaultFont()))) {
        LOG_ERROR("Default font isn't load");
    }
    int count = 0;
    for (auto const &[key, val]: pMsg) {
        DrawTextEx((*Mullemaus::Instance()->GetDefaultFont()), val.c_str(),
                   Vector2{pPosX, pPosY + (pTextSize * (count))}, pTextSize,
                   1, pTextColor);
        count++;
    }
}

void MM::MullemausOverlay::Update() {

}

void MM::MullemausOverlay::Clean() {
    LOG_DEBUG("Clean Overlay {}", pName);
    pMsg.clear();
    pNumLines = 0;
    pTextSize = Mullemaus::Instance()->GetDefaultFontSize();
    pName.clear();
}

void MM::MullemausOverlay::SetPos(float x, float y) {
    pPosY = y;
    pPosX = x;
}