#include <ros/ros.h>
#include <geometry_msgs/Twist.h> 
#include <stdlib.h> 
#include <beginner_tutorials/Pose.h>
#include <beginner_tutorials/Color.h>
# include <std_srvs/Empty.h>
/*
Simple program to control the turtle

rosrun turtlesim turtlesim_node
rosrun beginner_tutorials turtle

*/

beginner_tutorials::Pose pose;

void turtleCallback(const beginner_tutorials::Pose& msg)
{
  pose = msg;
  //ROS_WARN ("Turtle CallBack");
  //ROS_WARN_STREAM(msg);
}

int main(int argc, char **argv) {
     //Initializes ROS, and sets up a node
     ros::init(argc, argv, "random_move_commands");
     ros::NodeHandle nh;

     //Ceates the publisher, and tells it to publish
     //to the /turtle1/cmd_vel topic, with a queue size of 100
     ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 100);
     ros::Subscriber sub =nh.subscribe("/turtle1/pose",10, &turtleCallback); // Get the pose message from the turtle

     ros::ServiceClient client = nh.serviceClient<std_srvs::Empty>("/clear");
     std_srvs::Empty srv;

     //Sets up the random number generator
     srand(time(0));
    float temp_y,temp_x;
     //Sets the loop to publish at a rate of 10Hz
     ros::Rate rate(1);

        while(ros::ok()) {
         ros::spinOnce();
            //Declares the message to be sent
           geometry_msgs::Twist msg;
           //Random x value between -2 and 2
           msg.linear.x=4-3*double(rand())/double(RAND_MAX);
           //Random y value between -3 and 3
           msg.angular.z=6*double(rand())/double(RAND_MAX)-2;
           //Publish the message
            //ROS_WARN ("Turtle random Publish");
            //ROS_WARN_STREAM(pose);

            // Refresh the background with a randomly background color
            if ( rand() % 10 ==0){
            ros::param::set("/turtlesim/background_r", rand() % 255);
            ros::param::set("/turtlesim/background_b", rand() % 255);
            ros::param::set("/turtlesim/background_g",rand() % 255);
            client.call(srv);
            ROS_WARN ("Change background color");
            }

            // If the turtle hit the wall, give it one second to change direction
            //if(pose.x<=0||pose.y<=0||pose.x>=11||pose.y>=11)
            if(pose.x<=2||pose.y<=2||pose.x>=9||pose.y>=9)
            {              
              msg.linear.x = 6;
              if (pose.angular_velocity >= 0){
                msg.angular.z = 4;
              }else{
                msg.angular.z = -4;
              }
              
              pub.publish(msg);
              ROS_WARN_STREAM ("Change direction"<< rand() % 2);
              ros::Duration(0.2).sleep(); // sleep for half 2 seconds
            }
           pub.publish(msg);

          temp_x = pose.x; // the last x
          temp_y = pose.y; // the last x

          //Delays untill it is time to send another message
          rate.sleep();
         }
    
    return 0;
}