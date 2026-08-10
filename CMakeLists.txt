cmake_minimum_required(VERSION 4.3)
project(RedC C)

set(CMAKE_C_STANDARD 23)

find_package(SDL3 CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
        redc_main.c
        redc_math.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
