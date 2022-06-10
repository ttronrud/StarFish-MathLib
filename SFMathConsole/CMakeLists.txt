add_executable(SFMathConsole SFMathConsole.cpp)
target_link_libraries(SFMathConsole SFMath)
add_custom_command(TARGET SFMathConsole POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:SFMath>
        $<TARGET_FILE_DIR:SFMathConsole>)