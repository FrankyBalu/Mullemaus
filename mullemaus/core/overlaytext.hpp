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

#ifndef MULLEMAUSOVERLAY_H
#define MULLEMAUSOVERLAY_H

#include <string>
#include <map>
#include "mullemaus_api.hpp"
#include "basicobject.hpp"

typedef struct Color Color;

namespace MM {

    extern "C" {

    MULLEMAUS_API class OverlayText : public MM::BasicObject{
    public:
        OverlayText(std::string name);

        void AddText(const std::string msg);

        void RemoveText(long unsigned int line);

        void SetTextColor(Color color);

        void SetTextSize(int size);

        void SetPos(float x, float y);

        void Render();

        void Update();

        void Clean();

        bool Load(std::string initScript) override{return true;}

        void UnLoad() override{}

        void HandleInput() override{}

    private:

        std::map<int, std::string> pMsg;
        int pNumLines;
        float pTextSize;

        float pPosX;
        float pPosY;

        Color* pTextColor;

        std::string pName;
    };
    };
} // MM

#endif //MULLEMAUSOVERLAY_H
