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
#ifndef MULLEMAUS_LOG_HPP
#define MULLEMAUS_LOG_HPP


#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#define SPDLOG_NO_THREAD_ID
#define SPDLOG_USE_STD_FORMAT

#ifdef __PRETTY_FUNCTION__
# define SPDLOG_FUNCTION __PRETTY_FUNCTION__
#else
# define SPDLOG_FUNCTION __FUNCTION__
#endif

#ifdef _WIN32
#define NOGDI             // All GDI defines and routines
#define NOUSER            // All USER defines and routines
#endif

#include "spdlog/spdlog.h"

namespace MM {


    [[maybe_unused]] void Logger_Initialize();

    void Logger_Shutdown();

    void SetLogLevel(int level);

/**
 * Trace und Debug logging stehen im Release build  nicht zur verfügung
 */
#ifndef MULLEMAUS_RELEASE
/**
 * Sehr genaue Debugausgaben
 */
#define LOG_TRACE(...)    SPDLOG_TRACE(__VA_ARGS__)
/**
 * Norrmale Debugausgaben
 */
#define LOG_DEBUG(...)    SPDLOG_DEBUG(__VA_ARGS__)
#else
#define LOG_TRACE (...)     (void)0
#define LOG_DEBUG (...)	    (void)0
#endif

/**
 * @brief Allgemeine Informationen. Werden beim Initialisieren von MM und wenn zum Beispiel Module dazu geladen werden ausgegeben.
 * Für die Formatierung des Strings, siehe spdlog
 */
#define LOG_INFO(...)     SPDLOG_INFO(__VA_ARGS__)

/**
 * @brief Warnungen werden immer dann ausgegeben, wenn etwas nicht nach Plan läuft, aber das Programm ganz normal weiter Arbeiten kann.
 */
#define LOG_WARN(...)     SPDLOG_WARN(__VA_ARGS__)

/**
 * @brief Fehler, die nicht zum abbruch des Programms führen, aber den Programmfluss beeinflussen können.
 */
#define LOG_ERROR(...)    SPDLOG_ERROR(__VA_ARGS__)
/**
 * @brief Fehler, die so schwerwiegend sind, dass das Programm sofort beendet werden muss.
 */
#define LOG_FATAL(...)    SPDLOG_CRITICAL(__VA_ARGS__)

#define LOG_ASSERT(x, msg) if ((x)) {} else { LOG_FATAL("ASSERT - {}\n\t{}\n\tin file: {}\n\ton line: {}", #x, msg, __FILE__, __LINE__);}
} //namespace MM
#endif //MULLEMAUS_LOG_HPP