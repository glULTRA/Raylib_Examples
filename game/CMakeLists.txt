project(DigOut)

add_executable(DigOut DigOut.cpp)

include_directories(
    PUBLIC ../external/raylib/include/
)

link_directories(
    PRIVATE ../external/raylib/src/
)

IF(WIN32)
    target_link_libraries(DigOut raylib opengl32 winmm gdi32)
ELSEIF(UNIX)
    target_link_libraries(DigOut raylib)
ENDIF()