cmake_minimum_required(VERSION 2.8)

project(impprotobuf)

find_package(protobuf CONFIG REQUIRED)

message(STATUS "Using Protocol Buffers ${protobuf_VERSION_STRING}")

aux_source_directory(. SRC_LIST)

add_custom_command(
  OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/main.pb.cc"
         "${CMAKE_CURRENT_BINARY_DIR}/main.pb.h"
  COMMAND protoc
  ARGS --cpp_out ${CMAKE_CURRENT_BINARY_DIR} -I ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.proto
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/main.proto protoc
  COMMENT "Running C++ protocol buffer compiler on ${CMAKE_CURRENT_SOURCE_DIR}/main.proto"
  VERBATIM)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}
  ${SRC_LIST}
  ${CMAKE_CURRENT_BINARY_DIR}/main.pb.cc)

target_link_libraries(impprotobuf libprotobuf)

