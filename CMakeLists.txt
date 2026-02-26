cmake_minimum_required(VERSION 4.2.3)
project(EDF VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(EDF
  ${CMAKE_SOURCE_DIR}/src/main.cpp
  ${CMAKE_SOURCE_DIR}/src/Lexer.cpp
  ${CMAKE_SOURCE_DIR}/src/Utils.cpp
  ${CMAKE_SOURCE_DIR}/src/Parser.cpp
)

target_include_directories(EDF
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src/includes
)
