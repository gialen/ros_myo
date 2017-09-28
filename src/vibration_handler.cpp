#include <ros/ros.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/UInt8.h>

#define MAX_ACC_NORM 1.8

double left_acc_norm = 0.0;
double right_acc_norm = 0.0;

void left_acc_callback(const geometry_msgs::Vector3& msg)
{
	left_acc_norm = sqrt( pow(fabs(msg.x),2) + pow(fabs(msg.y),2) + pow(fabs(msg.z),2) );
}


void right_acc_callback(const geometry_msgs::Vector3& msg)
{
	right_acc_norm = sqrt( pow(fabs(msg.x),2) + pow(fabs(msg.y),2) + pow(fabs(msg.z),2) );
}

int main(int argc, char** argv)
{
	if(!ros::isInitialized()) ros::init(argc,argv,"vibration_shandler");
	ros::NodeHandle nh;
	ros::Subscriber left_sub = nh.subscribe("/left_imu_acc" ,1, left_acc_callback);
	ros::Subscriber right_sub = nh.subscribe("/right_imu_acc" ,1, right_acc_callback);
	ros::Publisher left_pub = nh.advertise<std_msgs::UInt8>("/For_l_vib",10);
	ros::Publisher right_pub = nh.advertise<std_msgs::UInt8>("/For_r_vib",10);
	std_msgs::UInt8 left_vib;
	std_msgs::UInt8 right_vib;

	ros::Rate loop(30);

	while(ros::ok())
	{
		left_vib.data = ( left_acc_norm < MAX_ACC_NORM )?0:1;
		right_vib.data = ( right_acc_norm < MAX_ACC_NORM )?0:1;

		if(left_vib.data) left_pub.publish(left_vib);
		if(right_vib.data) right_pub.publish(right_vib);

		
		// left_pub.publish(left_vib);
		// right_pub.publish(right_vib);

		ros::spinOnce();
		loop.sleep();
	}

	return 0;
}