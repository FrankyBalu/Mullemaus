project(mullemaus)

# Local source files here
set(MULLEMAUS_CORE
        src/core/log.cpp
        include/mullemaus/core/log.hpp
        #include/core/mullemaus.hpp
        #src/core/mullemaus_raylib.cpp
        #src/core/overlaytext_raylib.cpp
        #include/core/overlaytext.hpp
        #src/core/gamepad_raylib.cpp
        #include/core/gamepad.hpp
        #src/core/keyboard_raylib.cpp
        #include/core/keyboard.hpp
        #include/core/mullemaus_common.hpp
        #include/core/basicobject.hpp
        #src/core/rect2d.cpp
        #include/core/rect2d.hpp
        #src/core/overlaytextmanager.cpp
        #include/core/overlaytextmanager.hpp
        #src/core/objectfactory.cpp
        #include/core/objectfactory.hpp
        include/mullemaus/core/filesystem.hpp
        src/core/filesystem.cpp
        #src/core/texture2d.cpp
        #include/core/texture2d.hpp
        #include/core/font.hpp src/core/font.cpp
        src/core/window.cpp
        include/mullemaus/core/window.hpp
        include/mullemaus/core/Utils.hpp
        include/mullemaus/render/renderer.hpp
        include/mullemaus/render/color.hpp
        src/render/color.cpp
        src/render/renderer.cpp)

if (UNIX)
    if (BUILD_MULLEMAUS_SHARED)
        add_library(mullemaus_shared SHARED ${MULLEMAUS_CORE})
    endif ()
    if (BUILD_MULLEMAUS_STATIC)
        add_library(mullemaus_static STATIC ${MULLEMAUS_CORE})
    endif ()
elseif (WIN32)
    if (BUILD_MULLEMAUS_SHARED)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
        add_library(mullemaus_shared ${MULLEMAUS_CORE})
    endif ()
    if (BUILD_MULLEMAUS_STATIC)
        add_library(mullemaus_static STATIC ${MULLEMAUS_CORE})
    endif ()
endif ()

add_dependencies(mullemaus_shared version)
#add_dependencies(mullemaus_static version)

if (UNIX)
    target_link_libraries(mullemaus_shared
            raylib
            physfs
            spdlog
            )
else ()
    target_link_libraries(mullemaus_shared
            raylibdll.lib
            physfs.lib
            )
endif ()

if (UNIX)
    install(TARGETS mullemaus_shared
            EXPORT mullemaus
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            )

    INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/mullemaus
            FILES_MATCHING PATTERN "*.h*")
elseif (WIN32)
    install(TARGETS mullemaus
            EXPORT mullemaus
            LIBRARY DESTINATION "${PROJECT_BINARY_DIR}/../bin"
            ARCHIVE DESTINATION "${PROJECT_BINARY_DIR}/../bin"
            RUNTIME DESTINATION "${PROJECT_BINARY_DIR}/../bin"
            )
endif ()
