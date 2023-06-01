cmake_minimum_required(VERSION 3.5)

project(Fuzzy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenGL_GL_PREFERENCE GLVND)

add_executable(Fuzzy fuzzy.cpp)
