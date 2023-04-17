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

#include "objectfactory.hpp"
#include "basicobject.hpp"
#include "log.hpp"

MM::GameObjectFactory* MM::GameObjectFactory::pInstance = nullptr;

bool MM::GameObjectFactory::RegisterType(std::string typeID, BaseCreator *creator) {
    if (pCreators.count(typeID) != 0) {
        LOG_ERROR("Class with ID <{}> exists", typeID);
        delete creator;
        return false;
    } else {
        pCreators[typeID] = creator;
        LOG_TRACE("Regist new class <{}>", typeID);
        return true;
    }
}

MM::BasicObject* MM::GameObjectFactory::Create(std::string typeID) {
    if (pCreators.count(typeID) != 0) {
        BaseCreator *creator = pCreators[typeID];
        LOG_TRACE("Create object from class <{}>", typeID);
        return creator->CreateObject();
    } else {
        LOG_ERROR("Can not create object: unknown type <{}>", typeID);
        return nullptr;
    }
}