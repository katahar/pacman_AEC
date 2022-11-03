add_library(ConsumableClass consumable.h consumable.cpp)

target_include_directories(ConsumableClass PUBLIC .)

add_executable(consumableUnitTest MACOSX_BUNDLE unit_tests.cpp)
target_link_libraries(consumableUnitTest ConsumableClass)

add_test(NAME consumableTests COMMAND consumableUnitTest)