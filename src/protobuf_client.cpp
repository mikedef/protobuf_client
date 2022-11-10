/***************************************************************/                                       
/*    NAME: Michael DeFilippo and Supun Randeni                */                                       
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA  */                                       
/*    FILE: protobuf_client.cpp                                */                                       
/*    DATE: 2022-11-08                                         */
/*    NOTE: Node to connect to MOOS gateway and share data     */
/*          via a generic protobuf message                     */
/*                                                             */
/* This is unreleased BETA code. no permission is granted or   */                                       
/* implied to use, copy, modify, and distribute this software  */                                       
/* except by the author(s), or those designated by the author. */                                       
/***************************************************************/


#include <ros/ros.h>
#include <ros/console.h>

#include "gateway.pb.h"
#include "lib_gateway_tcp/tcp_client.h"
#include "util/protobuf_support_for_moos.h"
#include "lib_gateway_protobuf/gateway.pb.h"  // Eliminate? 


using namespace std;
using namespace boost;

#define __APP_NAME__ "protobuf_client"

void protobuf_client_callback(

int main(int argc, char **argv)
{
  // Init ROS
  ros::init (argc, argv, __APP_NAME__);
  ros::NodeHandle nh;
  ros::NodeHandle private_nh("~");

  //Spin
  ros::spin();
}
