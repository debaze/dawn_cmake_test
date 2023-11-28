cmake_minimum_required(VERSION 3.13)
project(app)
set(CMAKE_CXX_STANDARD 20)

add_executable(app "src/main.cpp")

if(EMSCRIPTEN)
	set_target_properties(app PROPERTIES OUTPUT_NAME "build" SUFFIX ".js")
	target_link_options(app PRIVATE "-O3" "-fexceptions" "-sEXPORT_ES6" "-sUSE_WEBGPU=1" "-sUSE_GLFW=3" "--embed-file=../../src@")
else()
	set(DAWN_FETCH_DEPENDENCIES ON)
	add_subdirectory("vendor/dawn" EXCLUDE_FROM_ALL)
	target_link_libraries(app PRIVATE webgpu_cpp webgpu_dawn webgpu_glfw)
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})