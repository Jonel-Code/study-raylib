cmake_minimum_required(VERSION 3.10.0)
project(Clicker VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)
set(RAYLIB_VERSION 5.5)

FetchContent_Declare(
    raylib_build
    URL https://github.com/raysan5/raylib/releases/download/${RAYLIB_VERSION}/raylib-${RAYLIB_VERSION}_win64_msvc16.zip
)
FetchContent_MakeAvailable(raylib_build)
add_library(raylib SHARED IMPORTED)

set(RAYLIB_DIR "${raylib_build_SOURCE_DIR}")
set_target_properties(raylib PROPERTIES
    IMPORTED_LOCATION "${RAYLIB_DIR}/lib/raylib.dll"
    IMPORTED_IMPLIB   "${RAYLIB_DIR}/lib/raylibdll.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_DIR}/include"
)

add_executable(Clicker main.cpp)
set_target_properties(Clicker PROPERTIES 
    LINK_FLAGS "/NODEFAULTLIB:MSVCRT"
)
target_compile_definitions(Clicker PRIVATE raylib)
target_link_libraries(Clicker PRIVATE raylib winmm)

add_custom_command(TARGET Clicker POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${RAYLIB_DIR}/lib/raylib.dll"
    $<TARGET_FILE_DIR:Clicker>
)