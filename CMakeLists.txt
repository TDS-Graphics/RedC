cmake_minimum_required(VERSION 4.3)
project(RedC C)

set(CMAKE_C_STANDARD 23)

find_package(SDL3 CONFIG REQUIRED)
find_package(cglm CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
        redc_main.c
        math_random.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 cglm::cglm)
