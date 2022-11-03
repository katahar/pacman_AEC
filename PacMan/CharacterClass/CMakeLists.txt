add_library(CharacterClass PC_Character.cpp PC_Character.h)

target_include_directories(CharacterClass PUBLIC .)

add_executable(characterUnitTest MACOSX_BUNDLE character_unit_test.cpp)
target_link_libraries(characterUnitTest CharacterClass)

add_test(NAME characterTest COMMAND characterUnitTest)