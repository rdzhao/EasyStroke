cmake_minimum_required(VERSION 3.1)

project(EasyStroke)

add_subdirectory(glm)

file(GLOB Headers "*.h")
file(GLOB Sources "*.cpp")

add_executable(EasyStroke ${Headers} ${Sources})

target_include_directories(EasyStroke PUBLIC glm)