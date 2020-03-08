// ROS Default Header File
#include "ros/ros.h"
#include "duckietown_msgs/WheelsCmdStamped.h"


int main(int argc, char **argv)
{
	ros::init(argc,argv, "line_following_node");
	ros::NodeHandle nh;
	
	ros::Publisher velocity_pub= nh.advertise<duckietown_msgs::WheelsCmdStamped>("duckiebot/wheels_driver_node/wheels_cmd", 1);

	ros::Rate loop_rate(10);

	duckietown_msgs::WheelsCmdStamped velocity_cmd;

	while(ros::ok())
	{
		velocity_cmd.vel_left= 0.2;
		velocity_cmd.vel_right= 0.2;
		velocity_pub.publish(velocity_cmd);
		loop_rate.sleep();
	}

	return 0;
}
