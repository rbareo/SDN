cmake_minimum_required(VERSION 4.2.3)
project(SDN VERSION 0.0.1 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SDN
  ${CMAKE_SOURCE_DIR}/src/main.cpp
  ${CMAKE_SOURCE_DIR}/src/Lexer.cpp
  ${CMAKE_SOURCE_DIR}/src/Utils.cpp
)

target_include_directories(SDN
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src/includes
)
