# protobuf_client package

`protobuf_client` is a ROS node that serves as a bridge to MOOS-IvP through a predefined Google Protobuf message type. It runs a TCP client using `lib_gateway_tcp` (adopted from https://github.com/GobySoft/netsim/tree/master/src/lib/tcp), which allows this application to connect to a MOOS based TCP server, using the same library.

When `protobuf_client` receives key-value pairs defined in the MOOS-IvP Gateway application. This data is posted as the rostopic `/gateway_msg` as Gateway.msg ROS type. The gateway_msg topic can then be subscribed to by an additional data parsing node created by the user.

The `protobuf_client` is set to automatically forward any messages posted to the topic specified by the `send_to_gateway_topic` parameter. This topics data type is of the custom Gateway.msg ROS type.

* Please see Gateway.msg for more information into the `/gateway_msg` and `/send_to_gateway` topics custom data type.

## ROS API

### Subs
* `send_to_gateway_topic` (msg/Gateway)

### Pubs
* `/gateway_msg` (msg/Gateway)
Received data from MOOS Gateway is published to this topic

### ROS Parameters
* `gateway_port`: default="9502"
  * Port number of MOOS Gateway
* `gateway_ip`:   default="127.0.0.1"
  * IP address of MOOS Gateway
* `send_to_gateway_topic`: default="/send_to_gateway_cora"
  * Subscribe to this topic to send data to MOOS



#### TODO:
* Need to fix proto generation so it builds to correct directory
  * Had to copy in the .pb.h .pb.c files into my include from build/protobuf_client/

