set(TARGET_NAME ghost_demo)
add_library(GhostClass Ghost.cpp Ghost.h GhostManager.cpp GhostManager.h GhostParams.h)
target_link_libraries(GhostClass MapClass)
target_include_directories(GhostClass PUBLIC .)
# add_executable(visualize MACOSX_BUNDLE Visualize.cpp)
add_executable(${TARGET_NAME} MACOSX_BUNDLE ghost_demo.cpp)
# target_link_libraries(visualize GhostClass)
target_link_libraries(${TARGET_NAME} GhostClass)

add_executable(ghost_test_1 MACOSX_BUNDLE scatter_test.cpp)
target_link_libraries(ghost_test_1 GhostClass)
add_test(NAME scatter_test COMMAND ghost_test_1)

add_executable(ghost_test_2 MACOSX_BUNDLE chase_test.cpp)
target_link_libraries(ghost_test_2 GhostClass)
add_test(NAME chase_test COMMAND ghost_test_2)

add_executable(ghost_test_3 MACOSX_BUNDLE collide_reverse_test.cpp)
target_link_libraries(ghost_test_3 GhostClass)
add_test(NAME collide_reverse_test COMMAND ghost_test_3)

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