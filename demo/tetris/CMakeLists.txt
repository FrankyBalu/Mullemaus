project(TetrisDemo)

SET(TETRIS_DEMO_SRC
        tetris.cpp
        )

add_executable(${PROJECT_NAME} ${TETRIS_DEMO_SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC mullemaus_shared
        )

if (UNIX)
    INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
elseif (WIN32)
    INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_BINARY_DIR}/../bin)
endif ()
