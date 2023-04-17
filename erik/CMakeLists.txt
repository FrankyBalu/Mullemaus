project(Erik)

SET(Erik_SRC
        erik.cpp
        )

add_executable(${PROJECT_NAME} ${Erik_SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC mullemaus
        )

if (UNIX)
    INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
elseif (WIN32)
    INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_BINARY_DIR}/../bin)
endif ()
