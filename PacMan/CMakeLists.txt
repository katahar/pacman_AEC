cmake_minimum_required(VERSION 3.8)
project(Pac-Man)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(CharacterClass)
add_subdirectory(GhostClass)
add_subdirectory(MapClass)
add_subdirectory(ConsumableClass)
add_subdirectory(PacManClass)
add_subdirectory(AnimationClass)
add_subdirectory(ScoreBoardClass)
add_subdirectory(SoundClass)

add_subdirectory(./public/src ${CMAKE_BINARY_DIR}/public)
add_subdirectory(./MMLPlayer/ym2612 ${CMAKE_BINARY_DIR}/ym2612)
add_subdirectory(./MMLPlayer/mmlplayer ${CMAKE_BINARY_DIR}/mmlplayer)
add_subdirectory(./simplebitmap ${CMAKE_BINARY_DIR}/simplebitmap)

set(TARGET_NAME PacMan)
add_executable(${TARGET_NAME} MACOSX_BUNDLE animationWithMapVelocity.cpp)

target_link_libraries(${TARGET_NAME} AnimationClass ScoreBoardClass ConsumableClass MapClass 
                     PacManClass GhostClass SoundClass yssimplesound yssimplesound_platform)

set(DATA_SOURCE ${CMAKE_SOURCE_DIR}/data)

get_property(IS_MACOSX_BUNDLE TARGET ${TARGET_NAME} PROPERTY MACOSX_BUNDLE)
if(MACOSX AND ${IS_MACOSX_BUNDLE})
    set(DATA_DESTINATION "$<TARGET_FILE_DIR:${TARGET_NAME}>/../Resources")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore")
    # YS_IS_UNIVERSAL_WINDOWS_APP is needed for ysgl to distinguish Win32 and UWP in VC
    add_definitions(-DYS_IS_UNIVERSAL_WINDOWS_APP)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /ZW")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /ZW")
    set(DATA_DESTINATION "$<TARGET_FILE_DIR:${TARGET_NAME}>/Assets")
elseif(MSVC)
    set(DATA_DESTINATION "$<TARGET_FILE_DIR:${TARGET_NAME}>")
else()
    set(DATA_DESTINATION "$<TARGET_FILE_DIR:${TARGET_NAME}>")
endif()

foreach(ONE_DATA_SOURCE ${DATA_SOURCE})
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD 
        COMMAND "${CMAKE_COMMAND}" -E make_directory \"${DATA_DESTINATION}\"
        COMMAND "${CMAKE_COMMAND}" -E copy_directory \"${ONE_DATA_SOURCE}\" \"${DATA_DESTINATION}\")
endforeach(ONE_DATA_SOURCE)
