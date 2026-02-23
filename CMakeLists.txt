cmake_minimum_required(VERSION 4.2.3)
project(EBF VERSION 0.0.1 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(EBF
  ${CMAKE_SOURCE_DIR}/src/main.cpp
  ${CMAKE_SOURCE_DIR}/src/Lexer.cpp
  ${CMAKE_SOURCE_DIR}/src/Utils.cpp
  ${CMAKE_SOURCE_DIR}/src/Parser.cpp
)

target_include_directories(EBF
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src/includes
)
