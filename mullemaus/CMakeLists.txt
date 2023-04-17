project(mullemaus)

# Local source files here
SET(MULLEMAUS_CORE
        core/log.cpp
        core/log.hpp
        core/mullemaus.hpp
        core/mullemaus.cpp
        core/MullemausOverlay.cpp
        core/MullemausOverlay.hpp
        core/gamepad.cpp
        core/gamepad.hpp
        core/keyboard.cpp
        core/keyboard.hpp
        )

if (UNIX)
    add_library(mullemaus SHARED ${MULLEMAUS_CORE})
else ()
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_library(mullemaus ${MULLEMAUS_CORE})
endif ()

add_dependencies(mullemaus version)

if (UNIX)
    target_link_libraries(mullemaus ${LUA_LIBRARY}
            raylib
            tinyxml2
            z
            physfs
            spdlog
            fmt
            )
else ()
    target_link_libraries(mullemaus lua54.lib
            raylibdll.lib
            libz.lib
            physfs.lib
            )
endif ()

if (UNIX)
    install(TARGETS mullemaus
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
