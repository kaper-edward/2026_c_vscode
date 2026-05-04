cmake_minimum_required(VERSION 3.20)

project(c11_course LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

function(enable_course_c11 target_name)
    if(MSVC)
        target_compile_options(${target_name} PRIVATE /W4)
    else()
        target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    if(WIN32)
        add_custom_command(TARGET ${target_name} PRE_LINK
            COMMAND ${CMAKE_COMMAND}
                -DTARGET_EXE=$<TARGET_FILE_NAME:${target_name}>
                -P ${CMAKE_SOURCE_DIR}/cmake/kill_if_running.cmake
            COMMENT "Stopping ${target_name} if running..."
        )
    endif()
endfunction()

add_subdirectory(labs)

