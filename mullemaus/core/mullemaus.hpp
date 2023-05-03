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

#ifndef MULLEMAUS_APP_HPP
#define MULLEMAUS_APP_HPP

#include "mullemaus_common.hpp"
#include "basicobject.hpp"
#include "overlaytext.hpp"
#include "overlaytextmanager.hpp"
#include "mullemaus_api.hpp"

#include <string>

typedef struct Font Font;

namespace MM {

    extern "C" {

    MULLEMAUS_API class Mullemaus {
    public:
        //! Gibt einen Zeiger auf eine Klassen Instance
        static Mullemaus *Instance();

        //! Initialisiert das Object der Klasse MM
        /*!
         * Hier werden alle Einstellungen geladen und das Fenster erstellt, in dem gerendert wird.
         * Desweiteren werden alle GameStates und GameObjekte, die fest zu MM gehören geladen.
         * Alle zu ladenden Dateien gehören in das Systemverzeichniss, das MM vorgibt (meist /usr/share/{Anwendungsname}
         * @param appName Name der Anwendung, wichtig für das laden von Dateien.
         * @return false, wenn irgendwas nicht geklappt hat
         */
        bool Initialize(const std::string &appName, int argc, char* argv[]);

        //! Ist MM initialisiert?
        /*!
         * Einige Funktionen sind darauf angewissen, das der OpenGl context geladen ist bzw die Einstellungen \n
         * diese können das hiermit überprüfen.
         *
         * @return true Wenn die Initialize-Funktion erfolgreich aufgerufen wurde
         */
        bool IsReady();

        //! Läuft die Haupptschleife von MM
        /*!
         * @return true, wenn die @sa RUN() läuft
         */
        bool IsRunning();

        //! Sorgt dafür das die Renderfunktion des aktuellen States aufgerufen wird
        /*!
         * Löscht den Bildschirminhalt und Rendert den aktuellen State, wenn Overlays vorhanden sind \n
         * werden diese nach dem State gerendert (z.B. Dialoge, InGameMenu (Itemmenu, CharakterMenu.....)
         */
        void Render();

        //! Löscht den Bildschirm auf die Festgelegte Hintergrundfarbe
        //TODO Hintergrundfarbe Benutzer definieren lassen
        void RenderClear();

        //! Update der Logik
        /*!
         * Die Updatefunktion des aktuellen States wird aufgerufen.
         * Hier sollte die Programmlogik/Ki-Funktionen abgearbeitet werden
         */
        void Update();

        //! Auf eingaben reagieren
        /*!
         * Die HandleEvents-Funktion des aktuellen States wird aufgerufen
         * Hier soll auf benutzer eingaben reagiert werden
         */
        void HandleEvents();

        //! Auflösung wurde geändert
        /*!
         * Diese Funktion sorgt dafür das alle States, nicht nur der Aktive, über die neue Auflösung informiert werden.
         */
        void Resize();

        //! Räumt den allokierten Speicher auf
        /*!
         * Diese Funktion Räumt den Speicher auf.
         * Wurde diese Funktion aufgerufen, musss neu Initialisiert werden @sa Initialize()
         */
        void Clean();

        //! Beendet den Mainloop
        /*!
         * Sorgt dafür das @sa Run() angehalten wird
         */
        void Quit();

        //! Gibt das Benutzer Verzeichnis zurück
        /*!
         * Hier können zum Beispiel Speicherstände abgelegt werden
         * @return Das Benutzerverzeichniss der Anwendung
         */
        std::string GetUserDir();

        //! Hauptschleife des Spiels
        /*!
         * Wenn diese Funktion aufgerufen wird, werden alle Update und Render-Funktionen in der richtigen \n
         * reihenfolge aufgerufen, bis das spiel beendet wird
         *
         */
        void Run();

        //! Gibt die Breite das Fensters/Bildschirm zurück
        int GetWindowWidth();

        //! Gibt die Höhe des Fensters/Bildschirms zurück
        int GetWindowHeight();

        //! Wechselt von/zu Vollbild
        bool SetFullscreen(bool fullscreen);

        //! Gibt den Defaultfont zurück
        Font* GetDefaultFont();

        //! Gibt die standard Schriftgröße zurück
        int GetDefaultFontSize();



        Mullemaus(const Mullemaus &) = delete;

        Mullemaus(Mullemaus &&) = delete;

        Mullemaus &operator=(const Mullemaus &) = delete;

        Mullemaus &operator=(Mullemaus &&) = delete;



        //zum Testen

        void AddTextOverlay(BasicObject *overlay);
    private:
        static Mullemaus *pInstance;

        Mullemaus();

        bool pIsReady;
        bool pRunning;
        std::string pAppName;
        std::string pAppDir;

        Font *pDefaultfont;
        int pFontSize;

        OverlayText *pOverlay;

        int pWindowWidth;
        int pWindowHeight;
        bool pStartInFullscreen;

        //Private Funktionen
        void CmdLineParser (int argc, char** argv);
        bool InitVideo();
        bool InitAudio();
        bool InitInput();

        TextOverlayManager pOverlayManager;
    };
    } //extern "C"
}//namespace MM

#endif //MULLEMAUS_APP_HPP
