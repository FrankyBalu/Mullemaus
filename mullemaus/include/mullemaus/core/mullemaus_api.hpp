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


#ifndef MULLEMAUS_API_HPP
#define MULLEMAUS_API_HPP

// Definitionen, falls MM unter windows als dll gebaut/genutzt werden soll
#ifdef _WIN32
#ifdef BUILD_LIBTYPE_SHARED
#define MULLEMAUS_API __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
#elifdef USE_LIBTYPE_SHARED
#define MULLEMAUS_API __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
#endif
#else
#ifndef MULLEMAUS_API
#define MULLEMAUS_API       // Functions defined as 'extern' by default (implicit specifiers)
#endif
#endif

#endif //MULLEMAUS_API_HPP
