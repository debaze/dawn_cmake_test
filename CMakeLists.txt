cmake_minimum_required(VERSION 3.13)
project(app)
set(CMAKE_CXX_STANDARD 20)

add_executable(app "src/main.cpp")

set(DAWN_FETCH_DEPENDENCIES ON)
add_subdirectory("vendor/dawn" EXCLUDE_FROM_ALL)
target_link_libraries(app PRIVATE webgpu_dawn webgpu_cpp webgpu_glfw)