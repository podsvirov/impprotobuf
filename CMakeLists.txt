cmake_minimum_required(VERSION 2.8)

project(impprotobuf)

# Uncomment to disable module compatible (by default is enabled)
#set(PROTOBUF_MODULE_COMPATIBLE OFF)

find_package(Protobuf CONFIG REQUIRED)

message(STATUS "Using Protocol Buffers ${PROTOBUF_VERSION_STRING}")

aux_source_directory(. SRC_LIST)

file(GLOB PROTO_LIST "*.proto")

if(NOT DEFINED PROTOBUF_MODULE_COMPATIBLE OR "${PROTOBUF_MODULE_COMPATIBLE}")

  include_directories(${PROTOBUF_INCLUDE_DIRS})
  protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_LIST})

else()

  set(PROTO_SRCS)
  set(PROTO_HDRS)

  foreach(FIL ${PROTO_LIST})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)

    list(APPEND PROTO_SRCS "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc")
    list(APPEND PROTO_HDRS "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h")

    add_custom_command(
      OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc"
             "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h"
      COMMAND protoc
      ARGS --cpp_out ${CMAKE_CURRENT_BINARY_DIR} -I ${CMAKE_CURRENT_SOURCE_DIR}
        ${ABS_FIL}
      DEPENDS ${ABS_FIL}
      COMMENT "Running C++ protocol buffer compiler on ${FIL}"
      VERBATIM)
  endforeach()

endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SRC_LIST} ${PROTO_SRCS} ${PROTO_HDRS})

if(NOT DEFINED PROTOBUF_MODULE_COMPATIBLE OR "${PROTOBUF_MODULE_COMPATIBLE}")
  target_link_libraries(impprotobuf ${PROTOBUF_LIBRARIES})
else()
  target_link_libraries(impprotobuf libprotobuf)
endif()

