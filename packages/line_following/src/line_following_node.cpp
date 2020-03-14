// ROS Default Header File
#include "ros/ros.h"
#include "duckietown_msgs/WheelsCmdStamped.h"

void straight(ros::Publisher velocity_pub){
	ros::Rate loop_rate(10);
	int count=0;

	duckietown_msgs::WheelsCmdStamped velocity_cmd;

	while(ros::ok())
	{
		velocity_cmd.vel_left= 0.3;
		velocity_cmd.vel_right= 0.3;
		velocity_pub.publish(velocity_cmd);
		ros::spinOnce();
		loop_rate.sleep();
		count++;
		if(count>20){
			count=0;
			break;
		}
	}

}
void turn_left(ros::Publisher velocity_pub){
	ros::Rate loop_rate(10);
	int count=0;

	duckietown_msgs::WheelsCmdStamped velocity_cmd;

	while(ros::ok())
	{
		velocity_cmd.vel_left= 0.0;
		velocity_cmd.vel_right= 0.3;
		velocity_pub.publish(velocity_cmd);
		ros::spinOnce();
		loop_rate.sleep();
		count++;
		if(count>6){
			count=0;
			break;
		}
	}

}

void stop(ros::Publisher velocity_pub){
	ros::Rate loop_rate(10);
	int count=0;

	duckietown_msgs::WheelsCmdStamped velocity_cmd;

	while(ros::ok())
	{
		velocity_cmd.vel_left= 0.0;
		velocity_cmd.vel_right= 0.0;
		velocity_pub.publish(velocity_cmd);
		ros::spinOnce();
		loop_rate.sleep();
		count++;
		if(count>10){
			count=0;
			break;
		}
	}

}

int main(int argc, char **argv)
{
	ros::init(argc,argv, "line_following_node");
	ros::NodeHandle nh;
	
	ros::Publisher velocity_pub= nh.advertise<duckietown_msgs::WheelsCmdStamped>("duckiebot/wheels_driver_node/wheels_cmd", 1);

	
	for(int i=4; i > 0; i--)
	{

		straight(velocity_pub);
		stop(velocity_pub);
		turn_left(velocity_pub);
		stop(velocity_pub);
	}

	ros::spin();
	return 0;
}
