#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <string>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 10);

  std_msgs::String msg;
  std::stringstream ss;
  ss << "hello world " ;//<< count;
  msg.data = ss.str();

  while (chatter_pub.getNumSubscribers() < 1 && ros::ok()) {
    //ROS_WARN("No subscribe for this topic");
    ros::Duration(0.5).sleep(); // sleep for half a second
  }     

  ros::Rate loop_rate(10);
  int count = 0;

  while (ros::ok())
  {    
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();  // ask ROS to handle callbacks
    
    loop_rate.sleep();
    ++count;
    if (count >=5){
      break;
    }    
  }
  return 0;
}