if (GIT_EXECUTABLE)
    message(${SRC})
    get_filename_component(SRC_DIR "${SRC}/CMakeLists.txt" DIRECTORY)
    # Generate a git-describe version string from Git repository tags
    execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --match "v*"
            WORKING_DIRECTORY ${SRC_DIR}
            OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
            RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (NOT GIT_DESCRIBE_ERROR_CODE)
        set(MULLEMAUS_VERSION_GIT ${GIT_DESCRIBE_VERSION})
    endif ()
endif ()

# Final fallback: Just use a bogus version string that is semantically older
# than anything else and spit out a warning to the developer.
if (NOT DEFINED MULLEMAUS_VERSION_GIT)
    set(MULLEMAUS_VERSION_GIT v0.0.0-unknown)
    message(WARNING "Failed to determine MULLEMAUS_VERSION from Git tags. Using default version \"${MULLEMAUS_VERSION_GIT}\".")
endif ()

configure_file(${SRC}/mullemaus/core/mullemaus_version.h.in ${DST} @ONLY)
