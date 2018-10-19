cmake_minimum_required(VERSION 3.5)
project(Krypto1)

set(CMAKE_CXX_STANDARD 14)
IF(CMAKE_BUILD_TYPE MATCHES "Release")
        set(CMAKE_CXX_FLAGS "-O3 -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free")
ELSE(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(CMAKE_CXX_FLAGS "-O0 -g -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -Wextra -Wpedantic -Wno-uninitialized")
ENDIF(CMAKE_BUILD_TYPE MATCHES "Release")

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/../cmake_modules
)

find_package(gtkmm)

set(SOURCE_FILES
        ../include/Application.h
        ../include/BlumMicaliGenerator.h
        ../include/CipherInterface.h
        ../include/MenuBar.h
        Application.cpp
        CipherDES.cpp
        CipherDSA.cpp
        CipherStream.cpp
        main.cpp
        MenuBar.cpp
)

INCLUDE_DIRECTORIES(
        ../include
        ${gtkmm_INCLUDE_DIRS}
)

add_executable(Krypto ${SOURCE_FILES})

set(ALL_LIBRARIES
        ${gtkmm_LIBRARIES}
)

target_link_libraries(Krypto ${ALL_LIBRARIES})

