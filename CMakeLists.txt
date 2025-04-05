cmake_minimum_required(VERSION 3.10)
project(SearchFiles)
file(GLOB SOURCES "*.cc")

add_executable(SearchFiles ${SOURCES})
