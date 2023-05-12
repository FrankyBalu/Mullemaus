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

#ifndef MULLEMAUS_FILESYSTEM_HPP
#define MULLEMAUS_FILESYSTEM_HPP

#include <string>
#include "mullemaus_api.hpp"

namespace MM {

    typedef struct Directory {
        unsigned int count;             // Anzahl der vorhandenen einträge
        char **entries;                 // Die einzelnen Elemente im Verzeichnis
    } Directory;

    extern "C" {

    MULLEMAUS_API class Filesystem {
    public:
        //! Initialisiert das Virtuelledateisystem
        /*! Es werden verschiedene standard Verzeichnisse angelegt und fixme
         * @return
         */
        static bool Init();

        static bool Close();

        static bool Mount(const std::string &dev, const std::string &mountPoint);

        static bool Unmount(const std::string &mountPoint);

        static bool FileExists(const std::string &filename);

        static bool DirectoryExists(const std::string &dirPath);

        static unsigned char *LoadFileData(const std::string &filename, unsigned int *bytesRead);

        static std::string LoadFileText(const std::string &filename);

        static bool SetWriteDir(const std::string &dirPath);

        static bool SaveFileData(const std::string &filename, const void *data, unsigned int bytesToWrite);

        static bool SaveFileText(const std::string &filename, std::string &text);

        static Directory LoadDirectory(const std::string &path);

        //fixme void durch einen eigenen Typen ersetzen
        //static Texture2D *LoadTexture(const char *filename);

        //fixme void durch einen eigenen Typen ersetzen
        //static void *LoadMusic(const char *filename);

        //fixme void durch einen eigenen Typen ersetzen
        //static void *LoadEffect(const char *filename);

        //fixme void durch einen eigenen Typen ersetzen
        //static Font *LoadFont(const char *filename, int size);

        static const char *GetAppPerfDirectory(const std::string &organization, const std::string &application);

        static const char *GetMullemausPerfDirectory();

    private:

        static bool isReady;

    };

    } //extern C
}//namespace MM

#endif //MULLEMAUS_FILESYSTEM_HPP
