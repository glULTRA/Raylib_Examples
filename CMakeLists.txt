cmake_minimum_required(VERSION 3.12.0)

project(Raylib)

add_subdirectory(external/raylib)
add_subdirectory(external/imgui/src)
add_subdirectory(examples)

add_executable(${PROJECT_NAME} main.cpp)

add_custom_target(always_rebuild ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/examples/res ${CMAKE_BINARY_DIR}/examples/res
)


target_include_directories(${PROJECT_NAME}
    PUBLIC ./external/raylib/include/
    PUBLIC ./external/imgui/include/
)

target_link_directories(${PROJECT_NAME}
    PUBLIC ./external/raylib/src/
    PUBLIC ./external/imgui/src/
)

IF(WIN32)
    target_link_libraries(${PROJECT_NAME} raylib  opengl32 gdi32 winmm)
ELSEIF(UNIX)
    target_link_libraries(${PROJECT_NAME} raylib)
ENDIF()