#include <ros/ros.h>
#include <ros_myo/EmgArray.h>
#include <geometry_msgs/Vector3.h>

geometry_msgs::Vector3 command;

#define CLOSURE_TH 150.0

void left_emg_callback(const ros_myo::EmgArray& msg)
{
	double value = 0.0;
	for(int i=0;i<msg.data.size();i++) value += msg.data[i];
	value = value/msg.data.size();
	command.x = (value > CLOSURE_TH)? 1.0 : 0.0;
}


void right_emg_callback(const ros_myo::EmgArray& msg)
{
	double value = 0.0;
	for(int i=0;i<msg.data.size();i++) value += msg.data[i];
	value = value/msg.data.size();
	command.y = (value > CLOSURE_TH)? 1.0 : 0.0;
}

int main(int argc, char** argv)
{
	command.x = 0.0;
	command.y = 0.0;
	command.z = 0.0;

	if(!ros::isInitialized()) ros::init(argc,argv,"emg_closures");
	ros::NodeHandle nh;
	ros::Subscriber left_sub = nh.subscribe("/For_l_emg" ,1, left_emg_callback);
	ros::Subscriber right_sub = nh.subscribe("/For_r_emg" ,1, right_emg_callback);
	ros::Publisher cmd_pub = nh.advertise<geometry_msgs::Vector3>("/closure",10);
	ros::Rate loop(100);

	while(ros::ok())
	{
		cmd_pub.publish(command);
		ros::spinOnce();
		loop.sleep();
	}

	return 0;
}