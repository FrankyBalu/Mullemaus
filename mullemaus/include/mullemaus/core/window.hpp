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


#ifndef MULLEMAUS_WINDOW_HPP
#define MULLEMAUS_WINDOW_HPP

#include <string>

#include "mullemaus_api.hpp"
#include "../include/mullemaus/render/color.hpp"

namespace MM {

    typedef enum {
        WINDOW_FLAG_VSYNC_HINT         = 0x00000040,   // Set to try enabling V-Sync on GPU
        WINDOW_FLAG_FULLSCREEN_MODE    = 0x00000002,   // Set to run program in fullscreen
        WINDOW_FLAG_WINDOW_RESIZABLE   = 0x00000004,   // Set to allow resizable window
        WINDOW_FLAG_WINDOW_UNDECORATED = 0x00000008,   // Set to disable window decoration (frame and buttons)
        WINDOW_FLAG_WINDOW_HIDDEN      = 0x00000080,   // Set to hide window
        WINDOW_FLAG_WINDOW_MINIMIZED   = 0x00000200,   // Set to minimize window (iconify)
        WINDOW_FLAG_WINDOW_MAXIMIZED   = 0x00000400,   // Set to maximize window (expanded to monitor)
        WINDOW_FLAG_WINDOW_UNFOCUSED   = 0x00000800,   // Set to window non focused
        WINDOW_FLAG_WINDOW_TOPMOST     = 0x00001000,   // Set to window always on top
        WINDOW_FLAG_WINDOW_ALWAYS_RUN  = 0x00000100,   // Set to allow windows running while minimized
        WINDOW_FLAG_WINDOW_TRANSPARENT = 0x00000010,   // Set to allow transparent framebuffer
        WINDOW_FLAG_WINDOW_HIGHDPI     = 0x00002000,   // Set to support HighDPI
        WINDOW_FLAG_WINDOW_MOUSE_PASSTHROUGH = 0x00004000, // Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED
        WINDOW_FLAG_MSAA_4X_HINT       = 0x00000020,   // Set to try enabling MSAA 4X
        WINDOW_FLAG_INTERLACED_HINT    = 0x00010000    // Set to try enabling interlaced video format (for V3D)
    } ConfigFlags;
    extern "C" {

    MULLEMAUS_API class Window {
    public:
        static bool Init(unsigned int width, unsigned int height, const std::string &title);
        static bool ShouldClose();
        static bool Close();
        static bool IsReady();
        static bool IsFullscreen();
        static bool IsHidden();
        static bool IsMinimized();
        static bool IsMaximized();
        static bool IsFocused();
        static bool IsResized();
        static bool HasFlag(unsigned int flag);
        static bool SetFlag(unsigned int flag);
        static bool ClearFlag(unsigned int flag);
        static void ToggleFullscreen();
        static void Maximize();
        static void Minimize();
        static void Restore();
        //FIXME Image existiert noch nicht
        //static void SetIcon(Image icon);
        static void SetTitle(const std::string &title);
        static void SetPosition(int x, int y);
        static void SetMonitor(int monitor);
        static void SetMinSize(int width, int height);
        static void SetSize(int width, int height);
        static void *GetHandle();
        static int GetWidth();
        static int GetHeight();
        static int GetMonitorCount();
        static int GetCurrentMonitor();
        //FIXME fehlender type
        //static vector2d GetMonitorPosition(int monitor);
        static int GetMonitorWidth(int monitor);
        static int GetMonitorHeight(int monitor);
        static int GetMonitorPhysicalWidth(int monitor);
        static int GetMonitorPhysicalHeight(int monitor);
        static int GetMonitorRefereshRate(int monitor);
        static std::string GetMonitorName(int monitor);

        //FIXME fehlender type
        // static vector2d GetPosition();
        // static vector2d GetScaleDPI ();
        //FIXME drag and drop
        // static void SetPosition(int x, int y);
        // static void SetPosition(int x, int y);

        static void ClearBackground (MM::Color color);
        static void BeginDrawing();
        static void EndDrawing();

        static std::string FlagToString(unsigned int flag);
    };//class Window
    }//extern C
}//namepsace MM
#endif //MULLEMAUS_WINDOW_HPP
