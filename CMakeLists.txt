cmake_minimum_required(VERSION 3.20)

project(courses-manager)

# Files
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.c)

list(APPEND TEST_FILES ${SOURCE_FILES})
list(REMOVE_ITEM TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

# Executables
add_executable(main ${SOURCE_FILES})
add_executable(test ${TEST_FILES})

# Include directories
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
