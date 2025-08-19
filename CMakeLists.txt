cmake_minimum_required(VERSION 3.26)
project(CrayonRuntime LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(CrayonRuntime
        Core/Main.cpp
        Core/Application.hpp
        Core/Application.cpp
        Core/Platform.hpp
        Core/Window.cpp
        Core/Window.hpp
        Core/Logger.hpp
        Core/Logger.cpp
        Core/GraphicsDevice.h
)

find_package(sdl3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

target_link_libraries(CrayonRuntime
        SDL3::SDL3-shared
        opengl32
        glad::glad
        glm::glm
        spdlog::spdlog
        imgui::imgui
        mingw32
)

set(VCPKG_DLL_DIR "${CMAKE_SOURCE_DIR}/Dependencies/vcpkg_installed/x64-mingw-dynamic/debug/bin")

# Release 빌드 시에는 debug/bin 대신 bin 폴더를 사용하도록 처리
if(CMAKE_BUILD_TYPE MATCHES "Release")
    set(VCPKG_DLL_DIR "${CMAKE_SOURCE_DIR}/Dependencies/vcpkg_installed/x64-mingw-dynamic/bin")
endif()


# 빌드가 끝난 후(POST_BUILD) 실행할 사용자 정의 명령 추가
add_custom_command(
        TARGET CrayonRuntime POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${VCPKG_DLL_DIR} $<TARGET_FILE_DIR:CrayonRuntime>
        COMMENT "Copying required DLLs to executable directory"
)