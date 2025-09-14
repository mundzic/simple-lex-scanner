cmake_minimum_required(VERSION 3.10.0)

project(yaxcom VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

file(COPY ${CMAKE_SOURCE_DIR}/src/cfg/c_grammar.cfg DESTINATION ${CMAKE_BINARY_DIR}/src/cfg)
file(COPY ${CMAKE_SOURCE_DIR}/src/calc.x DESTINATION ${CMAKE_BINARY_DIR}/src)


