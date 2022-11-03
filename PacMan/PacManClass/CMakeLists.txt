add_library(PacManClass PC_PacMan.cpp PC_PacMan.h)


target_link_libraries(PacManClass CharacterClass)
target_include_directories(PacManClass PUBLIC .)

add_executable(pacman_unit_test MACOSX_BUNDLE pacman_unit_test.cpp)
target_link_libraries(pacman_unit_test PacManClass)
add_test(NAME pacmanTests COMMAND pacman_unit_test)