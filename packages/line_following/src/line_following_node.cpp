// ROS Default Header File
#include "ros/ros.h"
#include "duckietown_msgs/WheelsCmdStamped.h"
#include "opencv2/highgui/highgui.hpp"
#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.h"


ros::Publisher pub_image;


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



void imageCallback(const sensor_msgs::CompressedImageConstPtr& msg)
{
    try
    {
        ROS_INFO_STREAM("image received ");
        cv::Mat image = cv::imdecode(cv::Mat(msg->data),1);//convert compressed image data to cv::Mat
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8" , image).toImageMsg();
        pub_image.publish(msg);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert to image!");
    }
}

int main(int argc, char **argv)
{
    ros::init(argc,argv, "line_following_node");
    ros::NodeHandle nh("~");

    ros::Publisher velocity_pub= nh.advertise<duckietown_msgs::WheelsCmdStamped>("/duckiebot/wheels_driver_node/wheels_cmd", 1);

    ros::Subscriber sub_image = nh.subscribe("/duckiebot/camera_node/image/compressed", 1, imageCallback);
    pub_image=nh.advertise<sensor_msgs::Image>("debug",1);


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
