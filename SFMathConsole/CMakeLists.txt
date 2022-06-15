add_executable(SFMathConsole SFMathConsole.cpp SFMathConsole.h)
target_link_libraries(SFMathConsole SFMath)

add_custom_command(TARGET SFMathConsole POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SFMath>
        $<TARGET_FILE_DIR:SFMathConsole>)

add_custom_command(TARGET SFMathConsole POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/RRs.txt
        $<TARGET_FILE_DIR:SFMathConsole>)