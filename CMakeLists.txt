# CMake configuration
cmake_minimum_required(VERSION 3.10)

project(subsonic VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Sources
set(subsonic_CODE_SOURCE_DIR ${subsonic_SOURCE_DIR}/src)

set(subsonic_SOURCES
    main.cxx
    files.cxx
    options.cxx
    embed.cxx)

list(TRANSFORM subsonic_SOURCES PREPEND
    "${subsonic_CODE_SOURCE_DIR}/")

add_executable(subsonic
    ${subsonic_SOURCES})

# Includes
file(GLOB subsonic_HEADERS ${subsonic_CODE_SOURCE_DIR}/*.hxx)

# Configuration header
configure_file(${subsonic_CODE_SOURCE_DIR}/config.hxx.in
    ${subsonic_CODE_SOURCE_DIR}/config.hxx)

# GNU gettext
set(subsonic_pot "${subsonic_SOURCE_DIR}/po/subsonic.pot")

add_custom_command(
    OUTPUT "${subsonic_pot}"
    WORKING_DIRECTORY "${subsonic_SOURCE_DIR}"
    COMMAND
        xgettext -k_ -c ${subsonic_SOURCES} ${subsonic_HEADERS} -o ${subsonic_pot})

add_custom_target(po-template
    DEPENDS "${subsonic_pot}")