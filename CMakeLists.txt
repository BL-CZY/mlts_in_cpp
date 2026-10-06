cmake_minimum_required(VERSION 3.23)

function(add_sources target dir)
    file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.cxx"
    )
    target_sources(${target} PRIVATE ${SOURCES})
endfunction()

# creates an executable that includes src/
# @param name: name for the binary
# @param main_path: path to the file containing the
# main function, will be appended to ${CMAKE_CURRENT_SOURCE_DIR}
# @param src_path: path to the rest of the sources,
# will be appended to ${CMAKE_CURRENT_SOURCE_DIR}
function(create_binary name main_path src_path)
    add_executable(${name})

    add_sources(${name} ${src_path})
    target_sources(${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${main_path})

    target_include_directories(${name}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${src_path})

    set_target_properties(${name}
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED on
        CXX_EXTENSIONS off
    )

    target_link_libraries(${name} PRIVATE ${LIBS})

    target_compile_options(${name}
    PRIVATE
        -Wall
        -Wextra
        # -Wpedantic
        # -Wconversion
        # -Wsign-compare
        # -Wshadow
        # -Wunused
        # -Wformat
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${name}
        PRIVATE
            -g
            -O0
            -DDEBUG
    )
    else()
        target_compile_options(${name}
        PRIVATE
            -O2
            -DNDEBUG
    )
    endif()
endfunction()

# @param name: name of test,
# @param src_path: path to the rest of the sources,
# will be appended to ${CMAKE_CURRENT_SOURCE_DIR}
function(create_test name src_path)
    create_binary(${name} test/${name}.cpp ${src_path})

    gtest_discover_tests(${name})
endfunction()

## dependencies

project(MLTS_Compiler_in_CPP)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

find_package(GTest REQUIRED)

SET(LIBS gtest::gtest
)

## binaries

create_binary(Compiler src/main.cpp src/mods)

## tests

enable_testing()
include(GoogleTest)

create_test(parser src/mods)
