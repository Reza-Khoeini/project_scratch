cmake_minimum_required(VERSION 3.16)
project(project_scratch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(project_scratch main.cpp)

if (WIN32)
    target_link_libraries(project_scratch PRIVATE mingw32 SDL2main SDL2)
else()
    find_path(SDL2_INCLUDE_DIR SDL.h PATH_SUFFIXES SDL2)
    find_library(SDL2_LIBRARY NAMES SDL2)

    if (SDL2_INCLUDE_DIR)
        target_include_directories(project_scratch PRIVATE ${SDL2_INCLUDE_DIR})
    endif()

    if (SDL2_LIBRARY)
        target_link_libraries(project_scratch PRIVATE ${SDL2_LIBRARY})
    else()
        message(WARNING "SDL2 library was not found. Install libsdl2-dev (or equivalent) to build.")
    endif()
endif()
