if(NOT TARGET_EXE)
    return()
endif()

execute_process(
    COMMAND taskkill /f /im "${TARGET_EXE}"
    RESULT_VARIABLE kill_result
    OUTPUT_QUIET
    ERROR_QUIET
)

if(kill_result EQUAL 0)
    execute_process(COMMAND "${CMAKE_COMMAND}" -E sleep 0.5)
endif()
