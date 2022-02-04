cmake_minimum_required(VERSION 3.12.0)

if (EMSCRIPTEN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so taht you can directly open it.
endif ()


project(Raylib)


add_subdirectory(external/raylib)
add_subdirectory(external/imgui/src)
add_subdirectory(examples)
add_subdirectory(game)

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