cmake_minimum_required(VERSION 3.24)

project(Mullemaus VERSION 0.0.0
        DESCRIPTION "Mullemaus dient als Framework bzw Engine für 2D Spiele. Erik ist eine Jump amd Run Demo uns Kleinod ist eine RPG Demo."
        LANGUAGES CXX)

#C++ Standart auf c++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FeatureSummary)

option(BUILD_SHARED_LIBS "Erstelle dynamische Bibliotheken" ON)
option(BUILD_DEMO_ERIK "Die Jump and Run Demo Erik bauen" ON)
option(BUILD_DEMO_KLEINOD "Die RPG Demo Kleinod bauen" ON)

########################################################################################################################
#                                                                                                                      #
#   Compilerflags												       #
#                                                                                                                      #
########################################################################################################################
if (UNIX)
    add_compile_options(-Wall -Wextra)
elseif (WIN32)
    #    add_compile_options(-Wall)
endif ()


########################################################################################################################
#                                                                                                                      #
#   CMake Buildtypes												       #
#                                                                                                                      #
########################################################################################################################
IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
            "Wähle einen Build-Type, möglichkeiten sind: None(CMAKE_CXX_FLAGS oder CMAKE_C_FLAGS benutzen) Debug Release RelWithDebInfo MinSizeRel."
            FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS None Debug Release RelWithDebInfo MinSizeRel)
ENDIF ()


########################################################################################################################
#                                                                                                                      #
#   Pfade zum installieren und um die Assets zu finden		                                                       #
#                                                                                                                      #
########################################################################################################################
if (UNIX)
    SET(BINDIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Wo die Programme installiert werden")
    SET(LIBDIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE PATH "Wo die Libs installiert werden")
    SET(DATAROOTDIR "${CMAKE_INSTALL_PREFIX}/share" CACHE PATH "Wurzelverzeichniss für daten")
    SET(ERIKDATADIR "${CMAKE_INSTALL_PREFIX}/share/games/Erik" CACHE PATH "Datenverzeichnis für Erik")
    SET(KLEINODDATADIR "${CMAKE_INSTALL_PREFIX}/share/games/Kleinod" CACHE PATH "Datenverzeichnis für Kleinod")
    SET(MULLEMAUSDATADIR "${CMAKE_INSTALL_PREFIX}/share/mullemaus" CACHE PATH "Mullemaus Datenverzeichnis")
    SET(ICONDIR "${DATAROOTDIR}/pixmaps" CACHE PATH "Icon Verzeichnis") #noch haben wir kein icon
else (WIN32)
    SET(ERIKDATADIR "data/")
    SET(KLEINODDATADIR "data/")
    SET(MULLEMAUSDATADIR "data/")
endif (UNIX)

########################################################################################################################
#                                                                                                                      #
#   Testen ob Doxygen vorhanden ist, um die API-Dokumentation zu generieren                                            #
#                                                                                                                      #
########################################################################################################################
find_package(Doxygen)
if (Doxygen_FOUND)
    add_subdirectory(docs)
else ()
    message(STATUS "Doxygen not found, not building docs")
endif ()
add_feature_info("Doxygen" Doxygen_FOUND "Generate API doc mir make doc")

########################################################################################################################
#                                                                                                                      #
#   Testen ob Librarys im system installiert sind oder ob die interne Kopie benutzt werden muss                        #
#                                                                                                                      #
########################################################################################################################

if (UNIX)
    find_package(Lua 5.4 REQUIRED)
    find_package(spdlog 1.11 REQUIRED)
    find_package(fmt 9.1 REQUIRED)
    find_package(tinyxml2 9.0 REQUIRED)

    #Sollte unter Linux immer vorhanden sein, glaub ich zumindest
    find_package(ZLIB 1.2 REQUIRED)
    find_package(PhysFS 3.2 REQUIRED)

    set(RAYLIB_VERSION 4.2.0)
    find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
    if (NOT raylib_FOUND) # If there's none, fetch and build raylib
        include(FetchContent)
        FetchContent_Declare(
                raylib
                URL https://github.com/raysan5/raylib/archive/refs/heads/master.zip
        )
        FetchContent_GetProperties(raylib)
        if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
            set(FETCHCONTENT_QUIET NO)
            FetchContent_Populate(raylib)
            set(BUILD_EXAMPLES OFF CACHE BOOL " " FORCE) # don't build the supplied examples
            set(BUILD_SHARED_LIBS OFF)
            set(USE_EXTERNAL_GLFW ON)
            set(CMAKE_BUILD_TYPE Release)
            set(WITH_PIC TRUE)
            add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR} EXCLUDE_FROM_ALL)
        endif ()
        include_directories(" ${raylib_SOURCE_DIR}/src")
    endif ()

    add_feature_info("System lua" LUA_FOUND "")
    add_feature_info("System zlib" ZLIB_FOUND "")
    add_feature_info("System tinyxml2" TINYXML2_FOUND "")
    add_feature_info("System spdlog" SPDLOG_FOUND "")
    add_feature_info("System fmt" FMT_FOUND "")
endif ()

########################################################################################################################
#                                                                                                                      #
#   Include Verzeichnisse hinzufügen                                                                                   #
#                                                                                                                      #
########################################################################################################################
if (UNIX)
    include_directories(
            "${PROJECT_BINARY_DIR}"
            "${PROJECT_SOURCE_DIR}"
            "${CMAKE_SYSTEM_INCLUDE_PATH}"
            "${PROJECT_SOURCE_DIR}/mullemaus/core/"
            "${PROJECT_SOURCE_DIR}/extra/"

            "${PROJECT_SOURCE_DIR}/extra/sol"
            "${LUA_INCLUDE_DIR}"
    )
else ()
    include_directories(
            "${PROJECT_SOURCE_DIR}/extra/lua-5.4.0/include"
            "${PROJECT_SOURCE_DIR}/extra/physfs-3.2.0/include"
            "${PROJECT_SOURCE_DIR}/extra/raylib-4.5.0/include"
            "${PROJECT_SOURCE_DIR}/extra/zlib-1.2.13/"
            "${PROJECT_SOURCE_DIR}/extra/tinyxml2"
            "${PROJECT_SOURCE_DIR}/extra/sol"
            "${PROJECT_SOURCE_DIR}/extra/spdlog"
            "${PROJECT_SOURCE_DIR}/extra"
            "${PROJECT_SOURCE_DIR}"
            "${PROJECT_BINARY_DIR}"
    )
    link_directories(
            "${PROJECT_SOURCE_DIR}/extra/lua-5.4.0/lib"
            "${PROJECT_SOURCE_DIR}/extra/physfs-3.2.0/lib"
            "${PROJECT_SOURCE_DIR}/extra/raylib-4.5.0/lib"
            "${PROJECT_SOURCE_DIR}/extra/zlib-1.2.13/"
    )
endif ()


if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(DEBUG 1)
endif ()

find_package(Git)
add_custom_target(version
        ${CMAKE_COMMAND} -D SRC=${CMAKE_SOURCE_DIR}
        -D DST=${CMAKE_BINARY_DIR}/mullemaus_version.h
        -D GIT_EXECUTABLE=${GIT_EXECUTABLE}
        -P ${CMAKE_SOURCE_DIR}/cmake/GenerateVersionHeader.cmake
        )


configure_file(${CMAKE_SOURCE_DIR}/mullemaus/core/globalConfig.hpp.in globalConfig.hpp)


########################################################################################################################
#                                                                                                                      #
#   Die ganzen unterverzeichnisse hinzufügen                                                                           #
#                                                                                                                      #
########################################################################################################################
add_subdirectory(extra)
add_subdirectory(mullemaus)
add_subdirectory(erik)
add_subdirectory(kleinod)
add_subdirectory(data)

message("  ")

if (UNIX)
    feature_summary(WHAT ENABLED_FEATURES DESCRIPTION "Enabled features:")
    feature_summary(WHAT DISABLED_FEATURES DESCRIPTION "Disabled features: ")
elseif (WIN32)
    message("Build for Windows")
    message("Nutzen interne kopien von LUA, TINYXML2, PHYSFS und ZLIB")
endif ()