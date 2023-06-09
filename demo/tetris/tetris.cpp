/*
 * Mullemaus - Tetris Demo
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

#include "mullemaus/render/color.hpp"
#include "raylib/src/raylib.h"
#include <mullemaus/core/filesystem.hpp>
#include <mullemaus/core/log.hpp>
#include <mullemaus/core/window.hpp>
#include <mullemaus/core/Utils.hpp>
#include <mullemaus/render/renderer.hpp>
#include <physfs.h>
#include <string>
#include <unistd.h>

const int BORDER = 6;
const int TILESIZE = 30;
const int PLAYGROUND_HEIGHT = 25;
const int PLAYGROUND_WIDTH = 15;
const int PRE_FRAME_WIDTH = TILESIZE * 4;
const int PRE_FRAME_HEIGHT = TILESIZE * 6;
const int SCORE_FRAME_WIDTH = TILESIZE * 6;
const int SCORE_FRAME_HEIGHT = TILESIZE;
const int PLAYFRAME_HEIGHT = TILESIZE * PLAYGROUND_HEIGHT + PLAYGROUND_HEIGHT;
const int PLAYFRAME_WIDTH = TILESIZE * PLAYGROUND_WIDTH + PLAYGROUND_WIDTH;
const int SCREEN_WIDTH = BORDER + PLAYFRAME_WIDTH + SCORE_FRAME_WIDTH + 100;
const int SCREEN_HEIGHT = (BORDER * 2) + PLAYFRAME_HEIGHT;
int NextFigure = 0;
int CurrentFigure = 0;
float TimerDelay = 0.3;
unsigned PlayerScore = 0;
bool MoveRight = false;
bool MoveLeft = false;
bool Rotate = false;
bool Pause = false;

int PLAYGROUND[PLAYGROUND_HEIGHT][PLAYGROUND_WIDTH];

struct Point {
    int x, y;
} aNext[4], b[4], aCurrent[4];

int Figures[7][4] = {
                1, 3, 5, 7, // I
                2, 4, 5, 7, // Z
                3, 5, 4, 6, // S
                3, 5, 4, 7, // T
                2, 3, 5, 7, // L
                3, 5, 7, 6, // J
                2, 3, 4, 5, // O
                };

MM::Color BackgroundColor = { 200, 200, 200, 255 };
MM::Color PlaygroundColor = {130, 130, 130, 255 };
MM::Color FrameColor = {80, 80, 80, 255};

MM::Color TileColor[7] = {
        {255, 0,   0,   255},
        {102, 191, 255, 255},
        {112, 31,  126, 255},
        {0,   228, 48,  255},
        {255, 161, 0,   255},
        {0,   121, 241, 255},
        {253, 249, 0,   255},
};


void DrawBackground() {
    //Frame für die Vorschau auf die nächste Figure
    MM::Renderer::DrawRect(BORDER + 50 + PLAYFRAME_WIDTH, BORDER, PRE_FRAME_WIDTH, PRE_FRAME_HEIGHT, FrameColor);
    //Frame für den Punktestand
    MM::Renderer::DrawRect(BORDER + 50 + PLAYFRAME_WIDTH, BORDER + 50 + PRE_FRAME_HEIGHT, SCORE_FRAME_WIDTH, SCORE_FRAME_HEIGHT, FrameColor);
    //Frame für das Spielfeld
    MM::Renderer::DrawRect(BORDER, BORDER, PLAYFRAME_WIDTH, PLAYFRAME_HEIGHT, PlaygroundColor);
    //Außenlinien des Spielfeldes
    MM::Renderer::DrawLine(BORDER, BORDER, BORDER, BORDER + PLAYFRAME_HEIGHT, MM::Color(200, 200, 200, 255));
    MM::Renderer::DrawLine(BORDER, BORDER, BORDER + PLAYFRAME_WIDTH, BORDER, MM::Color(200, 200, 200, 255));
    //Die Hilfslinien vom Spielfeld
    for (int i = 1; i <= PLAYGROUND_WIDTH; i++) {
        int xx = BORDER + (TILESIZE * i + i);
        MM::Renderer::DrawLine(xx, BORDER, xx, BORDER + PLAYFRAME_HEIGHT, MM::Color(200, 200, 200, 255));
    }
    for (int i = 1; i <= PLAYGROUND_HEIGHT; i++) {
        int yy = BORDER + (TILESIZE * i + i);
        MM::Renderer::DrawLine(BORDER, yy, BORDER + PLAYFRAME_WIDTH, yy, MM::Color(200, 200, 200, 255));
    }
}


void DrawNextFigure() {
    int offsetY = BORDER + TILESIZE; // Das Offset für die Y-Position
    int offsetX = BORDER + 50 + TILESIZE + PLAYFRAME_WIDTH; // Das Offset für die X-Position

    for (int i = 0; i < 4; i++) {
        MM::Renderer::DrawRect(offsetX + (aNext[i].x * TILESIZE), offsetY + (aNext[i].y * TILESIZE), TILESIZE, TILESIZE, TileColor[NextFigure]);
    }
}

void DrawCurrentFigure() {
    int offsetY;
    if (CurrentFigure == 0)
        offsetY = BORDER; // y-pos + tilegröße
    else
        offsetY = BORDER - TILESIZE; // y-pos + tilegröße
    int offsetX = BORDER;


    for (int i = 0; i < 4; i++) {
        MM::Renderer::DrawRect(offsetX + (aCurrent[i].x * TILESIZE) + aCurrent[i].x, offsetY + (aCurrent[i].y * TILESIZE) + aCurrent[i].y,
                               TILESIZE, TILESIZE, TileColor[CurrentFigure]);
    }
}

void DrawField() {
    for (int x = 0; x < PLAYGROUND_WIDTH; x++) {
        for (int y = 0; y < PLAYGROUND_HEIGHT; y++) {
            if (PLAYGROUND[y][x] != -1) {
                MM::Renderer::DrawRect(BORDER + x * (TILESIZE+1), BORDER + y * (TILESIZE+1) +1, TILESIZE, TILESIZE, TileColor[PLAYGROUND[y][x]]);
            }
        }
    }
}

bool CheckCollison() {
    for (int i = 0; i < 4; i++) {
        if (aCurrent[i].x < 0 || aCurrent[i].x >= PLAYGROUND_WIDTH || aCurrent[i].y >= PLAYGROUND_HEIGHT) {
            return true;
        }
        if (PLAYGROUND[aCurrent[i].y][aCurrent[i].x] != -1) {
            return true;
        }
    }
    return false;
};

void MoveDown() {
    for (int i = 0; i < 4; i++) {
        b[i] = aCurrent[i];
        aCurrent[i].y += 1;
    }

    if (CheckCollison()) {
        for (int i = 0; i < 4; i++) {
            PLAYGROUND[b[i].y][b[i].x] = CurrentFigure;
        }

        CurrentFigure = NextFigure;
        aCurrent[0] = aNext[0];
        aCurrent[1] = aNext[1];
        aCurrent[2] = aNext[2];
        aCurrent[3] = aNext[3];
        aCurrent[0].x += 4;
        aCurrent[1].x += 4;
        aCurrent[2].x += 4;
        aCurrent[3].x += 4;

        NextFigure = GetRandomValue(0, 6);
        for (int i = 0; i < 4; i++) {
            aNext[i].x = Figures[NextFigure][i] % 2;
            aNext[i].y = Figures[NextFigure][i] / 2;
        }

        if (!CheckCollison()) {
            LOG_ERROR("Verloren");

        }
    }
}

void DoMove() {
    if (MoveRight == true) {
        for (int i = 0; i < 4; i++) {
            b[i] = aCurrent[i];
            aCurrent[i].x += 1;
        }
        if (CheckCollison())
            for (int i = 0; i < 4; i++)
                aCurrent[i] = b[i];
    }
    if (MoveLeft == true) {
        for (int i = 0; i < 4; i++) {
            b[i] = aCurrent[i];
            aCurrent[i].x -= 1;
        }
        if (CheckCollison())
            for (int i = 0; i < 4; i++)
                aCurrent[i] = b[i];
    }
}

void DoRotate() {
    if (Rotate == true) {
        Point p = aCurrent[1]; //center of rotation
        for (int i = 0; i < 4; i++) {
            b[i] = aCurrent[i];
            int x = aCurrent[i].y - p.y;
            int y = aCurrent[i].x - p.x;
            aCurrent[i].x = p.x - x;
            aCurrent[i].y = p.y + y;
        }
        if (CheckCollison())
            for (int i = 0; i < 4; i++)
                aCurrent[i] = b[i];
    }
}

void CheckLine() {
    int k = PLAYGROUND_HEIGHT - 1;
    for (int i = PLAYGROUND_HEIGHT - 1; i > 0; i--) {
        int count = 0;
        for (int j = 0; j < PLAYGROUND_WIDTH; j++) {
            if (PLAYGROUND[i][j] != -1) {
                count++;
            }
            PLAYGROUND[k][j] = PLAYGROUND[i][j];
        }
        if (count < PLAYGROUND_WIDTH) {
            k--;
        } else {
            // increase user's score
            ++PlayerScore;
        }
    }
    if (k != 0) {
        std::fill(PLAYGROUND[0], PLAYGROUND[0] + (PLAYGROUND_WIDTH * (k + 1)), -1);
    }
}

void DrawScore() {
    std::string str_score;
    str_score = std::to_string(PlayerScore);
    DrawText("SCORE:", BORDER + PLAYFRAME_WIDTH + 50 + 2, BORDER + PRE_FRAME_HEIGHT + 50 + 2 , SCORE_FRAME_HEIGHT - 4, Color{127, 106, 79, 255});
    DrawText(str_score.c_str(), BORDER + PLAYFRAME_WIDTH + 50 + 2 + MeasureText("SCORE: ", SCORE_FRAME_HEIGHT - 4), BORDER + PRE_FRAME_HEIGHT + 50 + 2, SCORE_FRAME_HEIGHT - 4, Color{127, 106, 79, 255});
}

int main(int argc, char *argv[]) {
    MM::Filesystem::Init();

    MM::Window::Init(SCREEN_WIDTH, SCREEN_HEIGHT, "Mullemaus - Tetris Demo");
    MM::SetFPS(60);

    //TODO muss noch in die engine
    NextFigure = GetRandomValue(0, 6);
    CurrentFigure = GetRandomValue(0, 6);

    for (int i = 0; i < 4; i++) {
        aNext[i].x = Figures[NextFigure][i] % 2;
        aNext[i].y = Figures[NextFigure][i] / 2;
        aCurrent[i].x = Figures[CurrentFigure][i] % 2;
        aCurrent[i].y = Figures[CurrentFigure][i] / 2;
    }

    aCurrent[0].x += 4;
    aCurrent[1].x += 4;
    aCurrent[2].x += 4;
    aCurrent[3].x += 4;




    if (!MM::Window::ShouldClose()) {
        LOG_WARN ("Tweak to work at least with Fedora");
    }


    for (int i = 0; i < PLAYGROUND_WIDTH; i++){
        for (int o = 0; o < PLAYGROUND_HEIGHT; o++){
            PLAYGROUND[o][i] = -1;
        }
    }

    int timer = 0;
    while (!MM::Window::ShouldClose()) {
        //INPUT gedöns
        if (IsKeyPressed(KEY_LEFT))
            MoveLeft = true;
        else if (IsKeyPressed(KEY_RIGHT))
            MoveRight = true;
        else if (IsKeyPressed(KEY_UP))
            Rotate = true;
        else if (IsKeyDown(KEY_DOWN))
            TimerDelay = 0.05;

        if (timer >= 60 * TimerDelay){
            MoveDown();
            timer = 0;
        }
        else
            ++timer;

        DoMove();
        DoRotate();
        CheckLine();

        MM::Window::ClearBackground(BackgroundColor);

        MM::Renderer::BeginDrawing();

        DrawBackground();
        DrawField();
        DrawNextFigure();
        DrawCurrentFigure();
        DrawScore();
        MM::Renderer::EndDrawing();

        MoveLeft = false;
        MoveRight = false;
        Rotate = false;
        TimerDelay = 0.3;
    }

    return 0;
}
