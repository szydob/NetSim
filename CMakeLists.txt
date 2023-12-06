cmake_minimum_required(VERSION 3.22)

project(NetSim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

include_directories(include)

set(SOURCE_FILES
        src/helpers.cpp
        src/nodes.cpp
        src/package.cpp
        src/storage_types.cpp
        )

add_executable(NetSim ${SOURCE_FILES} main.cpp)

set(SOURCES_FILES_TESTS
        test/main_gtest.cpp
        test/test_nodes.cpp
        test/test_package.cpp
        test/test_storage_types.cpp
        )

add_executable(NetSim_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

target_include_directories(NetSim_test PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )

add_subdirectory(googletest-master)

target_link_libraries(NetSim_test gmock)

target_compile_definitions(NetSim_test PUBLIC EXERCISE_ID=EXERCISE_ID_NODES)