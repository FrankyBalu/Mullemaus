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
#ifndef MULLEMAUS_LOG_HPP
#define MULLEMAUS_LOG_HPP

#define SPDLOG_FMT_EXTERNAL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#ifdef __PRETTY_FUNCTION__
# define SPDLOG_FUNCTION __PRETTY_FUNCTION__
#else
# define SPDLOG_FUNCTION __FUNCTION__
#endif

#ifdef _WIN32
#define NOGDI             // All GDI defines and routines
#define NOUSER            // All USER defines and routines
#define SPDLOG_USE_STD_FORMAT
#include "spdlog/spdlog.h"
#else

#include <spdlog/spdlog.h>

#endif

namespace MM {


    void Logger_Initialize();

    void Logger_Shutdown();

#ifndef MULLEMAUS_RELEASE
#define LOG_TRACE(...)    SPDLOG_TRACE(__VA_ARGS__)
#define LOG_DEBUG(...)    SPDLOG_DEBUG(__VA_ARGS__)
#define LOG_INFO(...)     SPDLOG_INFO(__VA_ARGS__)
#define LOG_WARN(...)     SPDLOG_WARN(__VA_ARGS__)
#define LOG_ERROR(...)    SPDLOG_ERROR(__VA_ARGS__)
#define LOG_FATAL(...)    SPDLOG_CRITICAL(__VA_ARGS__)
#define LOG_ASSERT(x, msg) if ((x)) {} else { LOG_FATAL("ASSERT - {}\n\t{}\n\tin file: {}\n\ton line: {}", #x, msg, __FILE__, __LINE__);}
#else
    // Disable logging for release builds
#define LOG_TRACE (...)     (void)0
#define LOG_DEBUG (...)	    (void)0
#define LOG_INFO  (...)	    (void)0
#define LOG_WARN  (...)	    (void)0
#define LOG_ERROR (...)	    (void)0
#define LOG_FATAL (...)	    (void)0
#define LOG_ASSERT(x, msg)  (void)0
#endif
} //namespace MM
#endif //MULLEMAUS_LOG_HPP