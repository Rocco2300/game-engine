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

add_executable(game_engine main.cpp sources/shader.cpp)

target_include_directories(game_engine PUBLIC include)

target_link_libraries(game_engine glfw gl3w glm)