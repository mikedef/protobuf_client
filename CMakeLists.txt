cmake_minimum_required(VERSION 3.0.2)
project(protobuf_client)

add_compile_options(-std=c++14) 

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS
		    roscpp
		    std_msgs
		    genmsg
		    rospy
		    )

## System dependencies are found with CMake's conventions                                               
find_package(Boost REQUIRED COMPONENTS system)
find_package(Protobuf REQUIRED)                                                                    
                                                                                                        
message("libprotobuf >= 2.5.0")                                                                       
set(PROTOBUF_ALLOW_ALIAS "option allow_alias = true;")
set(Protobuf_INCLUDE_DIRS include/protobuf_client)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  Gateway.msg
  )

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

message("Checking: $ENV{HOME}")
#IF( EXISTS $ENV{HOME}/moos-ivp-gateway)
IF( EXISTS $ENV{HOME}/moos-ivp-champ)

# Specify where to find MITFrontseat's headers and libraries...
get_filename_component(MOOSGATEWAY_INC_DIR $ENV{HOME}/moos-ivp-champ/include ABSOLUTE)
get_filename_component(MOOSGATEWAY_LIB_DIR $ENV{HOME}/moos-ivp-champ/lib ABSOLUTE)
include_directories(${MOOSGATEWAY_INC_DIR})
LINK_DIRECTORIES(${MOOSGATEWAY_LIB_DIR})
message ("Found MOOSGateway in ${MOOSGATEWAY_INC_DIR}")

## Build 
include_directories(include include/protobuf_client ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIRS})
# lib/proto is a directory to store the raw gateway.proto msg
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS include/protobuf_client/ lib/proto/gateway.proto)
# NOTE: need to fix proto generation so it builds to correct directory
# Had to copy in the .pb.h .pb.c files into my include from build/protobuf_client/ 

#add_library(gateway_protobuf ${BUILD_STATIC_OR_SHARED_LIBRARIES} ${SRC} ${PROTO_SRCS} ${PROTO_HDRS})
add_library(gateway_protobuf include/protobuf_client/gateway.pb.cc)
#target_link_libraries(gateway_protobuf ${PROTOBUF_LIBRARIES})
#set_target_properties(gateway_protobuf PROPERTIES VERSION
#				       "${PROJECT_VERSION}" SOVERSION "${PROJECT_SOVERSION}")
				       
add_executable(protobuf_client
  nodes/protobuf_client.cpp
  nodes/protobuf_client_node.cpp)
  
target_link_libraries(protobuf_client ${catkin_LIBRARIES}
				      gateway_protobuf
				      ${PROTOBUF_LIBRARY}
				      gateway_tcp
				      )  # ${Boost_LIBRARIES})

ENDIF()


catkin_install_python(PROGRAMS scripts/publish_to_gateway.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
