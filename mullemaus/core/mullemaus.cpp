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


#include "mullemaus.hpp"
#include "log.hpp"
#include "keyboard.hpp"
#include <mullemaus_version.h>
#include <globalConfig.hpp>
#include <lyra/lyra.hpp>

#include <raylib.h>

#define RAYLIB_PHYSFS_IMPLEMENTATION

#include <raylib-physfs.h>


#define DEFAULT_FPS 60
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600


MM::Mullemaus *MM::Mullemaus::pInstance = nullptr;

MM::Mullemaus *MM::Mullemaus::Instance() {
    if (pInstance == nullptr)
        pInstance = new Mullemaus();
    return pInstance;
}


MM::Mullemaus::Mullemaus() : pIsReady(false), pRunning(false), pAppName(), pAppDir(), pFontSize(15) {
    pWindowWidth = DEFAULT_WINDOW_WIDTH;
    pWindowHeight = DEFAULT_WINDOW_HEIGHT;
}

bool MM::Mullemaus::Initialize(const std::string &appName, int argc, char* argv[]) {
    if (pIsReady) {
        LOG_FATAL("Mullemaus Engine already running!");
        return false;
    }
    //Den Logger starten
    Logger_Initialize();


    //Namen der Anwendung setzen
    pAppName = appName;
    LOG_INFO("Initialisiere Mullemaus Engine for {}", pAppName);
    LOG_INFO("\n\t\tMullemaus version: {}\n\t\tbuild with Raylib version: {}", MULLEMAUS_VERSION_GIT, RAYLIB_VERSION);

    //einige Raylib flags setzen
#ifdef RAYLIB_LOG
    SetTraceLogLevel(0); //damit werden alle Lognachrichten von Raylib unterbunden
    LOG_DEBUG("Enable Raylib logging");
#else
    SetTraceLogLevel(4); //damit werden alle Lognachrichten von Raylib unterbunden
    LOG_DEBUG("Raylib logging is disabled");
#endif

    CmdLineParser(argc, argv);



    InitVideo();
    InitAudio();
    InitInput();


    //Lade default font
    std::string Fontfile(MULLEMAUS_DATADIR + "/DefaultFont.ttf");
    pDefaultfont = new Font;
    (*pDefaultfont) = LoadFont(Fontfile.c_str());

    pOverlay = nullptr;
    pIsReady = true;
    pRunning = true;
    return true;


    /*#ifdef __linux__
    _AppDir = std::string(INSTALL_PREFIX) + std::string("/share/") + std::string(_AppName);
#else
    _AppDir = "data\\";
#endif


#ifdef __linux__
    InitPhysFSEx(_AppDir.c_str(), "system");
    MountPhysFS(GetPerfDirectory(" ", _AppName.c_str()), "user");
#else
    InitPhysFSEx("data/", "system");
    //MountPhysFS("data/", "user");
#endif
*/
}

std::string MM::Mullemaus::GetUserDir() {
    return GetPerfDirectory(" ", pAppName.c_str());
}

void MM::Mullemaus::Run() {
    while (!WindowShouldClose() && pRunning) {
        HandleEvents();
        Update();
        Render();
    }
}

bool MM::Mullemaus::IsReady() {
    return pIsReady;
}

void MM::Mullemaus::Render() {
    BeginDrawing();
    ClearBackground(Color{255, 255, 255, 255});

    if (pOverlay != nullptr) {
        pOverlay->Render();
    }

    EndDrawing();
}

void MM::Mullemaus::RenderClear() {
    BeginDrawing();
    ClearBackground(Color{255, 255, 255, 255});
    EndDrawing();
}

void MM::Mullemaus::Update() {
    //  if (!Dialog::Instance()->Exist()) {
    //      GameStateMaschine::Instance()->Update();
    // } else {
    //     Dialog::Instance()->Update();
    //}

}

void MM::Mullemaus::HandleEvents() {
/*    if (IsKeyPressed(KEY_F)) {
        ToggleFullscreen();
        Resize();
    }
    if (!Dialog::Instance()->Exist()) {
        GameStateMaschine::Instance()->HandleEvents();
    }*/
    if (WindowShouldClose()) {
        pRunning = false;
    }
}

bool MM::Mullemaus::IsRunning() {
    return pRunning;
}

void MM::Mullemaus::Quit() {
    pRunning = false;
}

int MM::Mullemaus::GetWindowWidth() {
    int width;
    if (IsWindowFullscreen()) {
        width = GetMonitorWidth(GetCurrentMonitor());
    } else {
        width = GetScreenWidth();
    }
    return width;
}

int MM::Mullemaus::GetWindowHeight() {
    int height;
    if (IsWindowFullscreen()) {
        height = GetMonitorHeight(GetCurrentMonitor());
    } else {
        height = GetScreenHeight();
    }
    return height;
}

bool MM::Mullemaus::SetFullscreen(bool fullscreen) {
    if (fullscreen && IsWindowFullscreen()) {
        return true;
    }
    if (fullscreen && !IsWindowFullscreen()) {
        LOG_DEBUG ("Change to fullscreen");
        SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
        //Zweimal RenderClear, damit auch unter Linux/X11 die richtige Vollbildauflösung angewendet wird
        RenderClear();
        RenderClear();
        ToggleFullscreen();
        return true;
    }
    if (!fullscreen && !IsWindowFullscreen()) {
        return true;
    }
    if (!fullscreen && IsWindowFullscreen()) {
        LOG_DEBUG("Change to windowed mode");
        ToggleFullscreen();
        SetWindowSize(pWindowWidth, pWindowHeight);
        return true;
    }
    return false;
}

void MM::Mullemaus::Resize() {
//    GameStateMaschine::Instance()->Resize();
}

Font* MM::Mullemaus::GetDefaultFont() {
    return pDefaultfont;
}

int MM::Mullemaus::GetDefaultFontSize() {
    return pFontSize;
}

void MM::Mullemaus::Clean() {
    if (!pIsReady) {
        LOG_FATAL("Can't clean up, Mullemaus is not initialized!");
        return;
    }
    LOG_DEBUG("Clean up Mullemaus");
    pAppName.clear();
    pFontSize = 0;
    pIsReady = false;
    UnloadFont((*pDefaultfont));
    CloseWindow();
}

//spielerein zum testen

void MM::Mullemaus::changeOverlay(MM::MullemausOverlay *overlay) {
    pOverlay = overlay;
}


void MM::Mullemaus::CmdLineParser(int argc, char **argv) {
    bool show_help = false;
    auto cmd =  lyra::cli();
    cmd.add_argument(lyra::help(show_help));
    cmd.add_argument(lyra::opt(pWindowWidth, "width")
                             .name ("--width")
                             .help("Window width"));
    cmd.add_argument(lyra::opt(pWindowHeight, "height")
                             .name ("--height")
                             .help("Window height"));
    cmd.add_argument(lyra::opt(pStartInFullscreen, "fullscreen")
                             .name ("--fullscreen")
                             .help("Start in fullscreen mode"));

    auto result = cmd.parse({ argc, argv });

    // Check that the arguments where valid:
    if (!result)
    {
        LOG_FATAL ("Error in command line: {}", result.message());
        std::cerr << cmd << std::endl;
        exit (1);
    }

    // Show the help when asked for.
    if (show_help)
    {
        std::cout << cmd << std::endl;
        exit (0);
    }
}

bool MM::Mullemaus::InitInput() {
    SetExitKey(static_cast<int>(MM::KEY::ESCAPE)); //F12
    return true;
}

bool MM::Mullemaus::InitAudio() {
    InitAudioDevice();
    return true;
}

bool MM::Mullemaus::InitVideo() {
    LOG_TRACE("Set FPS to {}", DEFAULT_FPS);
    SetTargetFPS(DEFAULT_FPS);

    LOG_TRACE("Enable MSAA x4");
    SetConfigFlags(FLAG_MSAA_4X_HINT);


    LOG_TRACE("Create window");
    if (pStartInFullscreen) {
        int monitor = GetCurrentMonitor();
        LOG_ERROR("Monitor: {}", monitor);
        InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), pAppName.c_str());
    }
    else{
        InitWindow(pWindowWidth, pWindowHeight, pAppName.c_str());
    }

    if (!IsWindowReady()) {
        LOG_FATAL("Can't create the window!");
        return false;
    }
    return true;
}
