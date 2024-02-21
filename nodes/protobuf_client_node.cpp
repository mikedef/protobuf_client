/***************************************************************/
/*    NAME: Michael DeFilippo (mikedef@mit.edu)                */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA  */
/*    FILE: MOOSGateway.h                                      */
/*    DATE: 2022-11-04                                         */
/* Copyrght MIT and author/s of software.                      */
/* This is unreleased BETA code. no permission is granted or   */
/* implied to use, copy, modify, and distribute this software  */
/* except by the author(s), or those designated by the author. */
/***************************************************************/

#include "protobuf_client.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, __APP_NAME__);

  ProtobufClient app;

  app.Run();

  return 0;
}
