cmake_minimum_required(VERSION 3.26)
project(CrayonEngine LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(CrayonEngine.exe System/Main.cpp)

find_package(SDL3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
endif()

target_link_libraries(CrayonEngine.exe
        SDL3::SDL3-static
        glad::glad
        glm::glm
        imgui::imgui
        opengl32
        mingw32
)
