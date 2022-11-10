#ifndef PROTOBUF_CLIENT_H
#define PROTOBUF_CLIENT_H
#define __APP_NAME__ "protobuf_client"

// ROS includes
#include <ros/ros.h>                                                                                    
#include <ros/console.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include "protobuf_client/Gateway.h"
// Protobuf
#include "gateway.pb.h"
// Gateway Includes
#include "lib_gateway_tcp/tcp_client.h"       // Bring into ws so I don't have to link to MOOS lib      
#include "util/protobuf_support_for_moos.h"   // Eliminate? Don't need to serialize? 
#include "lib_gateway_protobuf/gateway.pb.h"  // Eliminate? Already set up proto through catkin

class ProtobufClient
{
  ros::NodeHandle nh_;
  ros::Publisher pub_gateway_msg_;
  ros::Subscriber sub_to_gateway_;
  unsigned int gateway_port_;
  std::string gateway_ip_;
  boost::asio::io_service io_;
  std::shared_ptr<gateway::tcp_client> client_{gateway::tcp_client::create(io_)};
  
  void ToGatewayCallback(const protobuf_client::Gateway &msg);
  /** 
   * @brief callback to subscribe to client ros gateway msgs and post to MOOSDB
   * @param[in] msg
   **/

  void ConnectToGateway();
  /**
   * @brief Connect to the MOOSDB through TCP 
   **/

  void IngestGatewayMsg();
  /**
   * @brief Ingests msg from gateway and publishes as a custom Gateway ROS msg
   **/

  void Iterate();
  /**
   * @brief Loop continuously through the Iterate function at the desired rate
   **/

  void InitRosIO(ros::NodeHandle &in_private_nh);
  /**
   * @brief callback to inititialize parameters 
   * @param[in] in_private_nh
   **/

  
  
 public:
  void Run();
 ProtobufClient();
  virtual ~ProtobufClient();
};

#endif // PROTOBUF_CLIENT_H
