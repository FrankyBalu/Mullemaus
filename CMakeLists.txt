cmake_minimum_required(VERSION 3.24)

project(Mullemaus
	VERSION 0.0.0
	DESCRIPTION "Mullemaus ist ein Engine für für 2D Spiele"
	LANGUAGES CXX)
	
#c++ Standart auf c++ 23 setzen
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include (FeatureSummary)
#Optionen für das Bauen
option(BUILD_MULLEMAUS_SHARED "Erstelle die dynamische Bibliothek" ON)
option(BUILD_MULLEMAUS_STATIC "Erstelle die statische Bibliothek" OFF)
option(BUILD_DEMOS "Erstellt die Demos zu Mullemaus" ON)

if (NOT BUILD_MULLEMAUS_SHARED AND NOT MULLEMAUS_STATIC)
    message("Es muss entweder static oder shared gebaut werden")
    return()
endif()

#Optionen für abhängigkeiten
option(MULLEMAUS_USE_SYSTEM_PHYSFS "Wenn verfügbar System PhysFS verwenden" ON)
option(MULLEMAUS_USE_SYSTEM_SPDLOG "Wenn verfügbar System SPDLog verwenden" ON)
option(MULLEMAUS_USE_SYSTEM_RAYLIB "Wenn verfügbar System Raylib verwenden" ON)

#Optionen für die Dokumentation
option(MULLEMAUS_BUILD_API_DOC "API Dokumentation erstellen" OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#Compiler Flags
if (UNIX)
    add_compile_options(-Wall -Wextra)
elseif (WIN32)
    add_compile_options(/Wall)
endif ()

#Buildtype
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Wähle einen Build-Type, möglichkeiten sind: Debug Release" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(ENABLE_DEBUG 1)
endif ()

#Version für die Git basierte Version
find_package(Git)
if (Git_FOUND)
	
	add_custom_target(version
	${CMAKE_COMMAND} -D SRC=${CMAKE_SOURCE_DIR}
        -D DST=${CMAKE_BINARY_DIR}/mullemaus_version.h
        -D GIT_EXECUTABLE=${GIT_EXECUTABLE}
        -P ${CMAKE_SOURCE_DIR}/cmake/GenerateVersionHeader.cmake
        )
else()
	set(MULLEMAUS_VERSION_GIT ${PROJECT_VERSION})
        configure_file(${SRC}/mullemaus/src/core/mullemaus_version.h.in ${DST} @ONLY)
endif()

#Installationsverzeichnisse
if (UNIX)
    SET(MULLEMAUSDATADIR "${CMAKE_INSTALL_PREFIX}/share/mullemaus" CACHE PATH "Mullemaus Datenverzeichnis")
else (WIN32)
    SET(MULLEMAUSDATADIR "data/")
endif (UNIX)

#Configurationsheader schreiben
configure_file(${CMAKE_SOURCE_DIR}/mullemaus/src/core/globalConfig.hpp.in globalConfig.hpp)

#Doxygen für die API Dokumentation
find_package(Doxygen)
if (Doxygen_FOUND)
	if (MULLEMAUS_BUILD_API_DOC)
    		add_subdirectory(docs)
    		add_feature_info("Doxygen" Doxygen_FOUND "Erstelle API Dokumentation")
    	endif()
    	add_feature_info("Doxygen" Doxygen_FOUND "Üerspringe API Dokumentation")
else ()
    message(STATUS "Doxygen nicht gefunden, baue keine API Dokumentation")
    add_feature_info("Doxygen" Doxygen_FOUND "Erstelle API Dokumentation")
endif ()

#abhängigkeiten Prüfen
find_package(spdlog QUIET)
if (NOT MULLEMAUS_USE_SYSTEM_SPDLOG OR NOT spdlog_FOUND)
    if (UNIX)
    	#wird benötigt um Mullemaus shared zu bauen
        #set(SPDLOG_BUILD_PIC ON)
        #wir bauen spdlog static, damit es beim installieren keine Systemlib überschreibt
        set(SPDLOG_BUILD_SHARED OFF)
    else ()
        set(SPDLOG_BUILD_SHARED ON)
    endif ()
    add_subdirectory(extra/spdlog)
    set(SPDLOG_INCLUDE_DIR extra/spdlog/include)
endif ()

find_package(physfs QUIET)
if (NOT MULLEMAUS_USE_SYSTEM_PHYSFS)
#SS	if (NOT physfs_FOUND)
    	if (UNIX)
    	#wird benötigt um Mullemaus shared zu bauen
        #set(SPDLOG_BUILD_PIC ON)
        #wir bauen spdlog static, damit es beim installieren keine Systemlib überschreibt
        set (PHYSFS_BUILD_SHARED FALSE)
        set (PHYSFS_BUILD_STATIC TRUE)
    else ()
        set (PHYSFS_BUILD_SHARED TRUE)
        set (PHYSFS_BUILD_STATIC FALSE)
    endif ()
    add_subdirectory(extra/physfs)
#    set(PHYSFS_INCLUDE_DIR extra/physfs/src)
endif ()

find_package(raylib QUIET)
if (NOT MULLEMAUS_USE_SYSTEM_RAYLIB OR NOT raylib_FOUND)
    if (UNIX)
        find_package(glfw QUIET)
        if (glfw_FOUND)
            set (USE_EXTERNAL_GLFW ON)
        set (WITH_PIC ON)
        set (BUILD_SHARED_LIBS OFF)
    else ()
        set (BUILD_SHARED_LIBS ON)
        endif ()
    endif ()
    set (BUILD_EXAMPLES OFF)
    add_subdirectory(extra/raylib)
endif ()


#include Verzeichnisse
include_directories(
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}"
        "${CMAKE_SYSTEM_INCLUDE_PATH}"
        "${PROJECT_SOURCE_DIR}/mullemaus/include/"
        "${PROJECT_SOURCE_DIR}/mullemaus/include/core/"
        "${PROJECT_SOURCE_DIR}/extra/"
        "${PROJECT_SOURCE_DIR}/extra/lyra/include"
        #"${LUA_INCLUDE_DIR}"
    	)
    	
#Verzeichnisse hinzufügen
add_subdirectory(mullemaus)
if (BUILD_DEMOS)
add_subdirectory(demo/tetris)
endif ()
#add_subdirectory(data)

macro(message_bool_option _NAME _VALUE)
    if(${_VALUE})
        message(STATUS "  ${_NAME}: enabled")
    else()
        message(STATUS "  ${_NAME}: disabled")
    endif()
endmacro()

message("")
message("")
message("")
message("")
message(STATUS "Mullemaus Optonen:")
message_bool_option("Build Shared: " BUILD_MULLEMAUS_SHARED)
message_bool_option("Build Static: " BUILD_MULLEMAUS_STATIC)
if (MULLEMAUS_BUILD_API_DOC AND Doxygen_FOUND)
	message_bool_option("Build API Doc: " MULLEMAUS_BUILD_API_DOC)
elseif (MULLEMAUS_BUILD_API_DOC AND NOT Doxygen_FOUND)
	message_bool_option("Build API Doc: " Doxygen_FOUND)
elseif (NOT MULLEMAUS_BUILD_API_DOC AND Doxygen_FOUND)
	message_bool_option("Build API Doc: " MULLEMAUS_BUILD_API_DOC)
endif()	
message("")
message("")
message(STATUS "Build Demos:")
message_bool_option("Demos: " BUILD_DEMOS)
message("")
message("")
message(STATUS "Abhängigkeiten:")
message_bool_option("System SpdLog:" spdlog_FOUND)
message_bool_option("Benutze System SpdLog: " MULLEMAUS_USE_SYSTEM_SPDLOG)
message_bool_option("System PhysFS:" physfs_FOUND)
message_bool_option("Benutze System Physfs: " MULLEMAUS_USE_SYSTEM_PHYSFS)
message_bool_option("System Raylib:" raylib_FOUND)
message_bool_option("Benutze System Raylib: " MULLEMAUS_USE_SYSTEM_RAYLIB)

















