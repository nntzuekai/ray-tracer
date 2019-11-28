cmake_minimum_required(VERSION 3.10)
project(Project3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)


LINK_DIRECTORIES(lib)
link_libraries(glut)
link_libraries(GLEW)
link_libraries(GL)

add_executable(rayT primitive.cpp primitive.h defs.h ray_trace.cpp tracer.cpp tracer.h InitShader.cpp)
target_link_libraries(rayT glut GLEW)