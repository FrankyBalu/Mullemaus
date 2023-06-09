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


#include "../../include/mullemaus/core/window.hpp"
#include "../../include/mullemaus/core/log.hpp"
#include "mullemaus/render/color.hpp"
#include <raylib.h>


bool MM::Window::Init(unsigned int width, unsigned int height, const std::string &title) {
    InitWindow(width, height, title.c_str());
    if (!IsReady()){
        LOG_FATAL("Konnte Fenster nicht erstellen!");
        return false;
    }
    LOG_DEBUG("Fenster {} mit Breite {} und Höhe {}", title, width, height);
    return true;
}

bool MM::Window::ShouldClose() {
    return WindowShouldClose();
}

bool MM::Window::Close() {
    CloseWindow();
    bool returnValue = IsReady();
    if (returnValue){
        LOG_ERROR ("Konnte Fenster nicht schließen");
    }
    return returnValue;
}

bool MM::Window::IsReady() {
    return IsWindowReady();
}

bool MM::Window::IsFullscreen() {
    return IsWindowFullscreen();
}

bool MM::Window::IsHidden() {
    return IsWindowHidden();
}

bool MM::Window::IsMinimized() {
    return IsWindowMinimized();
}

bool MM::Window::IsMaximized() {
    return IsWindowMaximized();
}

bool MM::Window::IsFocused() {
    return IsWindowFocused();
}

bool MM::Window::IsResized() {
    return IsWindowResized();
}

bool MM::Window::HasFlag(unsigned int flag) {
    bool returnVal = IsWindowState(flag);
    if (returnVal){
        LOG_DEBUG("Fenster hat Flag {}", FlagToString(flag));
    }
    else{
        LOG_DEBUG("Fenster hat Flag {} nicht", FlagToString(flag));
    }
    return returnVal;
}

bool MM::Window::SetFlag(unsigned int flag) {
    SetWindowState(flag);
    bool returnVal = HasFlag(flag);
    if (returnVal)
        return true;
    LOG_WARN("Konnte Flag {} nicht setzen", FlagToString(flag));
    return false;
}

bool MM::Window::ClearFlag(unsigned int flag) {
    ClearWindowState(flag);
    if (HasFlag(flag))
        return false;
    else
        return true;
}

void MM::Window::ToggleFullscreen() {
    ::ToggleFullscreen();
}

void MM::Window::Maximize() {
    MaximizeWindow();
}

void MM::Window::Minimize() {
    MinimizeWindow();
}

void MM::Window::Restore() {
    RestoreWindow();
}

void MM::Window::SetTitle(const std::string &title) {
    SetWindowTitle(title.c_str());
}

void MM::Window::SetPosition(int x, int y) {
    //TODO teste ob es im möglichen bereich des Monitors liegt
    SetWindowPosition(x, y);
}

void MM::Window::SetMonitor(int monitor) {
    if (monitor > 0 && monitor < MM::Window::GetMonitorCount()){
        LOG_ERROR("Kann nicht auf Monitor {} wechseln, Monitor nicht vorhanden", monitor);
        return;
    }
    SetWindowMonitor(monitor);
}

void MM::Window::SetMinSize(int width, int height) {
    SetWindowMinSize(width, height);
}

void MM::Window::SetSize(int width, int height) {
    SetWindowSize(width, height);
}

void *MM::Window::GetHandle() {
    return GetWindowHandle();
}

int MM::Window::GetWidth() {
    return GetScreenWidth();
}

int MM::Window::GetHeight() {
    return GetScreenHeight();
}

int MM::Window::GetMonitorCount() {
    return ::GetMonitorCount();
}

int MM::Window::GetCurrentMonitor() {
    return ::GetCurrentMonitor();
}

int MM::Window::GetMonitorWidth(int monitor) {
    return ::GetMonitorWidth(monitor);
}

int MM::Window::GetMonitorHeight(int monitor) {
    return ::GetMonitorHeight(monitor);
}

int MM::Window::GetMonitorPhysicalWidth(int monitor) {
    return ::GetMonitorPhysicalWidth(monitor);
}

int MM::Window::GetMonitorPhysicalHeight(int monitor) {
    return ::GetMonitorPhysicalHeight(monitor);
}

int MM::Window::GetMonitorRefereshRate(int monitor) {
    return ::GetMonitorRefreshRate(monitor);
}

std::string MM::Window::GetMonitorName(int monitor) {
    return ::GetMonitorName(monitor);
}

void MM::Window::ClearBackground(MM::Color color) {
    ::ClearBackground({color.r,color.g,color.b,color.a});
}

void MM::Window::BeginDrawing() {
    ::BeginDrawing();
}

void MM::Window::EndDrawing() {
    ::EndDrawing();
}

std::string MM::Window::FlagToString(unsigned int flag) {
    switch (flag) {
        case WINDOW_FLAG_VSYNC_HINT:
            return "VSYNC";
        case WINDOW_FLAG_FULLSCREEN_MODE:
            return "Fullscreen";
        case WINDOW_FLAG_WINDOW_RESIZABLE:
            return "Resizeable";
        case WINDOW_FLAG_WINDOW_UNDECORATED:
            return "Undecorated";
        case WINDOW_FLAG_WINDOW_HIDDEN:
            return "Hidden";
        case WINDOW_FLAG_WINDOW_MINIMIZED:
            return "Minimized";
        case WINDOW_FLAG_WINDOW_MAXIMIZED:
            return "Maximized";
        case WINDOW_FLAG_WINDOW_UNFOCUSED:
            return "Unfocused";
        case WINDOW_FLAG_WINDOW_TOPMOST:
            return "Allways on top";
        case WINDOW_FLAG_WINDOW_ALWAYS_RUN:
            return "Allways run";
        case WINDOW_FLAG_WINDOW_TRANSPARENT:
            return "Transparent";
        case WINDOW_FLAG_WINDOW_HIGHDPI:
            return "HighDPI";
        case WINDOW_FLAG_WINDOW_MOUSE_PASSTHROUGH:
            return "Mouse passthrough";
        case WINDOW_FLAG_MSAA_4X_HINT:
            return "MSAA x4";
        case WINDOW_FLAG_INTERLACED_HINT:
            return "Interlaced";
        default:
            return std::string("Unbekannt");
    }
}