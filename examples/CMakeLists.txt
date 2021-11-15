project(circle_gardient)
project(mousePosition)

add_executable(circle_gardient circle_gardient.cpp)
add_executable(mousePosition mousePosition.cpp)

include_directories(
    PUBLIC ../external/raylib/include/
)

link_directories(
    PRIVATE ../external/raylib/src/
)

IF(WIN32)
    target_link_libraries(circle_gardient raylib opengl32 gdi32 winmm)
    target_link_libraries(mousePosition raylib opengl32 gdi32 winmm)
ENDIF()
