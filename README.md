# protobuf_client

ROS node that serves as a bridge to MOOS-IvP through a predefined Google Protobuf message type. protobuf_client receiveds key-value pairs defined in the MOOS-IvP Gateway application. This data is posted as the rostopic "/gateway_msg". The gateway_msg topic can then be subscribed to by an additional data parsing node created by the user.
* Please see Gateway.msg for more information into the gateway_msg topic custom data type. 

#### Notes:
