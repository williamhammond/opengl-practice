cmake_minimum_required(VERSION 3.23)
project(opengl_practice)

set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

include(FetchContent)
FetchContent_Declare(glfw
        GIT_REPOSITORY git@github.com:glfw/glfw.git
        GIT_TAG 3.3
        )
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(glm
        GIT_REPOSITORY git@github.com:g-truc/glm.git
        GIT_TAG origin/master
        )
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
        GIT_TAG origin/master
)
FetchContent_GetProperties(glew)
if (NOT glew_POPULATED)
    FetchContent_Populate(glew)

    add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()


add_executable(opengl_practice main.cpp mesh.cpp mesh.h shader.cpp shader.h)

target_link_libraries(opengl_practice libglew_static glfw glm)