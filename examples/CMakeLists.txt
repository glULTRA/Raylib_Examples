project(circle_gardient)
project(mousePosition)
project(checkCollisionPointRec)
project(randomPixelWalking)
project(frameCounter)

add_executable(circle_gardient circle_gardient.cpp)
add_executable(mousePosition mousePosition.cpp)
add_executable(checkCollisionPointRec checkCollisionPointRec.cpp)
add_executable(randomPixelWalking randomPixelWalking.cpp)
add_executable(frameCounter frameCounter.cpp)

include_directories(
    PUBLIC ../external/raylib/include/
)

link_directories(
    PRIVATE ../external/raylib/src/
)

IF(WIN32)
    target_link_libraries(circle_gardient raylib opengl32 gdi32 winmm)
    target_link_libraries(mousePosition raylib opengl32 gdi32 winmm)
    target_link_libraries(checkCollisionPointRec raylib opengl32 gdi32 winmm)
    target_link_libraries(randomPixelWalking raylib opengl32 gdi32 winmm)
    target_link_libraries(frameCounter raylib opengl32 gdi32 winmm)
ENDIF()
