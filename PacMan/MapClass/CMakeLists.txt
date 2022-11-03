add_library(MapClass map.h map.cpp)

target_link_libraries(MapClass fssimplewindow ConsumableClass AnimationClass)
target_include_directories(MapClass PUBLIC .)

add_executable(mapUnitTest MACOSX_BUNDLE map_unit_test.cpp)
target_link_libraries(mapUnitTest MapClass)

add_test(NAME mapTests COMMAND mapUnitTest)