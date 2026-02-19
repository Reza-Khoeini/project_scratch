cmake_minimum_required(VERSION 4.0)
project(project_scratch)

set(CMAKE_CXX_STANDARD 20)

add_executable(project_scratch main.cpp
        Pen.h
        Pen.cpp
        UI.h
        UI.cpp
        Drawlayer.h
        Drawlayer.cpp
        ColorUtil.h
        ColorUtil.cpp
        UICallback.h
        UICallback.cpp
        khoeini1.h
        khoeini2.h)
target_link_libraries(${PROJECT_NAME} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer)