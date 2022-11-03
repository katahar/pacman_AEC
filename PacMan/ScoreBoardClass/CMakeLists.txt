add_library(ScoreBoardClass scoreboard.h scoreboard.cpp)

target_link_libraries(ScoreBoardClass ysbitmapfont fssimplewindow)
target_include_directories(ScoreBoardClass PUBLIC .)

add_executable(scoreUnitTest MACOSX_BUNDLE score_unit_test.cpp)
target_link_libraries(scoreUnitTest ScoreBoardClass)

add_test(NAME scoreTests COMMAND scoreUnitTest)