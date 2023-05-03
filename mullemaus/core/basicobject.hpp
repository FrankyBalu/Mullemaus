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

#ifndef MULLEMAUS_BASICOBJECT_HPP
#define MULLEMAUS_BASICOBJECT_HPP

#include "mullemaus_api.hpp"
#include "rect2d.hpp"
#include <string>

namespace MM {

    extern "C" {

    MULLEMAUS_API class BasicObject {
    public:
        virtual bool Load(std::string initScript) = 0;

        virtual void UnLoad() = 0;

        virtual void Render() = 0;

        virtual void Update() = 0;

        virtual void HandleInput() = 0;

        virtual std::string GetClass(){
            return pClass;
        }

        virtual std::string GetType(){
            return pType;
        }

        virtual std::string GetName(){
            return pName;
        }

        virtual unsigned long int GetID(){
            return pID;
        }

        virtual unsigned long int GetObjectCount(){
            return pIDCount;
        }

        Rect2D GetRect2D(){
            return pRect;
        }

    protected:
        BasicObject(std::string oclass, std::string type, std::string name): pClass(oclass), pType(type), pName(name){
            pID = pIDCount;
            pIDCount++;
        }
        virtual ~BasicObject(){}

        std::string pClass;
        std::string pType;
        std::string pName;

        long unsigned int pID;

        Rect2D pRect;

    private:
        static long unsigned int pIDCount;
    };

    }

} // MM

#endif //MULLEMAUS_BASICOBJECT_HPP
