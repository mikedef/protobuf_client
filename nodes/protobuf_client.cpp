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


#include "protobuf_client.h"

ProtobufClient::ProtobufClient()
{
  // Constructor
}

void ProtobufClient::ToGatewayCallback(const protobuf_client::Gateway &msg)
{
  // transform msg data to protobuf 
  moos::gateway::ToGateway to_gateway;
  ros::Time time = ros::Time::now();
  to_gateway.set_client_time(time.toSec());
  to_gateway.set_client_key(msg.gateway_key);
  to_gateway.set_client_string(msg.gateway_string);
  to_gateway.set_client_double(msg.gateway_double);
  
  //ROS_INFO("Client Key: %s", msg.gateway_key.c_str());
    
  // send to MOOS
  if(client_->connected())
  {
    client_->write(to_gateway);
  }
}

void ProtobufClient::ConnectToGateway()
{
  ROS_INFO("Connecting to iMOOSGateway...");
  bool print_loop_error = false;
  client_->connect(gateway_ip_, gateway_port_);
  while (!client_->connected())
  {
    client_->connect(gateway_ip_, gateway_port_);
    usleep(10000);
    try
    {
      io_.poll();
    }
    catch(boost::system::error_code & ec)
    {
      if (!print_loop_error)
      {
	ROS_INFO("Looping until connected to gateway. Error ");
	std::cout << ec << std::endl;
      }
    }
  }
  ROS_INFO("Connected to gateway");

  // Send kickoff message to gateway
  moos::gateway::ToGateway msg;
  ros::Time time = ros::Time::now();
  msg.set_client_time(time.toSec());
  msg.set_client_key("NAV_TEST");
  msg.set_client_double(0.0);
  msg.set_client_string(" ");

  if (client_->connected())
  {
    ROS_INFO("Sending kickoff msg: %s", msg.ShortDebugString().c_str());
    client_->write(msg);
  }
}

void ProtobufClient::IngestGatewayMsg()
{
  client_->read_callback<moos::gateway::FromGateway>(
    [this](const moos::gateway::FromGateway& msg,
	   const boost::asio::ip::tcp::endpoint& ep)
      {
	// Create Gateway msg
	protobuf_client::Gateway gateway_msg;
	gateway_msg.gateway_time = ros::Time::now();  // Update for actual moos time msg.gateway_time
	gateway_msg.header.stamp = ros::Time::now();
	gateway_msg.gateway_key = msg.gateway_key();
	gateway_msg.gateway_string = msg.gateway_string();
	gateway_msg.gateway_double = msg.gateway_double();
	// Publish Gateway msg
	pub_gateway_msg_.publish(gateway_msg);
	ROS_INFO("Received Gateway Key: %s", gateway_msg.gateway_key.c_str());
      });
}

void ProtobufClient::InitRosIO(ros::NodeHandle &in_private_nh)
{
  // init params
  gateway_port_ = 1024;
  // TODO: Add to launch and add check for param that goes to a default if not set
  ROS_INFO("[%s] gateway_port: %d", __APP_NAME__, gateway_port_);
  gateway_ip_ = "127.0.0.1"; // TODO: Add to launch and a check for IP
  ROS_INFO("[%s] gateway IP: %s", __APP_NAME__, gateway_ip_.c_str());

  // Connecting to iMOOSGateway
  ConnectToGateway();

  // Define handles for interface messages
  IngestGatewayMsg();
  
  // init subscriptions
  sub_to_gateway_ = nh_.subscribe("/send_to_gateway", 1, &ProtobufClient::ToGatewayCallback, this);

  // init publishers
  pub_gateway_msg_ = nh_.advertise<protobuf_client::Gateway>("/gateway_msg", 1000);
}

void ProtobufClient::Iterate()
{
  // Maintaining the TCP connection
  if (client_->connected()){
    io_.poll();
  }
  else {
    ROS_INFO("Disconnected from Gateway...");
    // Try to reconnect
    client_->connect(gateway_ip_, gateway_port_);
    try                                                                                             
    {                                                                                                   
      io_.poll();                                                                                       
    }                                                                                                   
    catch(boost::system::error_code & ec)                                                               
    {                                                                                                   
      ROS_INFO("Looping until connected to gateway. Error ");                                         
      std::cout << ec << std::endl;                                                                   
    }
  }
}

void ProtobufClient::Run()
{
  ros::NodeHandle private_nh("~");

  InitRosIO(private_nh);

  ros::Rate loop_rate(20);  // add var for loop_rate

  while (ros::ok())
  {
    Iterate();
    ros::spinOnce();
    loop_rate.sleep();
  }

  
}

ProtobufClient::~ProtobufClient()
{
  // Destructor
}


