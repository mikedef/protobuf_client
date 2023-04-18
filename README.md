# protobuf_client

`protobuf_client` is a ROS node that serves as a bridge to MOOS-IvP through a predefined Google Protobuf message type. It runs a TCP client using `lib_gateway_tcp` (adopted from https://github.com/GobySoft/netsim/tree/master/src/lib/tcp), which allows this application to connect to a MOOS based TCP server, using the same library.

When `protobuf_client` receiveds key-value pairs defined in the MOOS-IvP Gateway application. This data is posted as the rostopic `/gateway_msg` as Gateway.msg ROS type. The gateway_msg topic can then be subscribed to by an additional data parsing node created by the user.

The `protobuf_client` is set to automatically forward any messages posted to the `/send_to_gateway` topic. This topics data type is of the custom Gateway.msg ROS type.

* Please see Gateway.msg for more information into the `/gateway_msg` and `/send_to_gateway` topics custom data type.





#### Notes:
* Need to fix proto generation so it builds to correct directory
  * Had to copy in the .pb.h .pb.c files into my include from build/protobuf_client/

