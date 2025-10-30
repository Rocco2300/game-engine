cmake_minimum_required(VERSION 3.31)
project(game_engine)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        gl3w
        GIT_REPOSITORY https://github.com/skaslev/gl3w.git
)
FetchContent_MakeAvailable(gl3w)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG 1.0.2
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
        fast_obj
        GIT_REPOSITORY https://github.com/thisistherk/fast_obj.git
        GIT_TAG v1.3
)
FetchContent_MakeAvailable(fast_obj)

FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v6.0.2
)
set(BUILD_SHARED_LIBS ON)
FetchContent_MakeAvailable(assimp)

add_executable(
        game_engine
        main.cpp
        sources/shader.cpp
        sources/program.cpp
        sources/mesh.cpp
        sources/model.cpp
        sources/camera.cpp
        sources/input.cpp
        sources/fps_camera.cpp
)

target_include_directories(game_engine PUBLIC include)

target_link_libraries(game_engine glfw gl3w glm assimp)