add_library(AnimationClass animation.cpp animation.h)
target_link_libraries(AnimationClass fssimplewindow simplebitmap) 
target_include_directories(AnimationClass PUBLIC .)

add_executable(animationUnitTest MACOSX_BUNDLE animation_unit_test.cpp)
target_link_libraries(animationUnitTest AnimationClass)

add_test(NAME animationTests COMMAND animationUnitTest)

# add_custom_command( TARGET AnimationClass POST_BUILD
#                     COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/sprites/)
# add_custom_command( TARGET AnimationClass POST_BUILD
#                     COMMAND ${CMAKE_COMMAND} -E copy_directory
#                     ${CMAKE_SOURCE_DIR}/sprites/ ${CMAKE_BINARY_DIR}/sprites/)
