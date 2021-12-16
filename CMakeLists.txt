cmake_minimum_required(VERSION 3.12.0)

project(Raylib)

add_subdirectory(external/raylib)
add_subdirectory(examples)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ./external/raylib/include/
)

target_link_directories(${PROJECT_NAME}
    PUBLIC ./external/raylib/src/
)

IF(WIN32)
    target_link_libraries(${PROJECT_NAME} raylib opengl32 gdi32 winmm)
ELSEIF(UNIX)
    target_link_libraries(${PROJECT_NAME} raylib)
ENDIF()