add_library(SoundClass sound.h sound.cpp)

target_link_libraries(SoundClass yssimplesound yssimplesound_platform)
target_include_directories(SoundClass PUBLIC .)