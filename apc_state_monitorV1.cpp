/*
System monitor for the CSM Amazon Picking Challenge
Team Blaster

created 4/23/2015 by Andrew Neill (aneill@mines.edu)
last update 4/23/2015 Andrew Neill

Few items to review:
1. What topics are we listening to?
2. What message format are they in?
3. is there some way to do a callback that will work for any topic?

*/

#include <ros/ros.h>
#include <message_event.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <std_msgs/Float32.h>




// See section 2.4 of : http://wiki.ros.org/roscpp/Overview/Publishers%20and%20Subscribers
void labjackCallback(const ros::MessageEvent<std_msgs::Float32 const>& event)
{
  ros::Time receipt_time = event.getReceiptTime();
  if (ros::Time::now() - receipt_time > timeThresh)
  	nh.setParam(labJackParam, true);
  else
  	nh.setParam(labJackParam, false);

  //nh.setParam(labJackParam, (bool)(current_time - receipt_time > timeThresh));

  //const std_msgs::StringConstPtr& msg = event.getMessage();
}



int main(int argc, char** argv)
{
	ros::init(argc, argv, "apc_state_monitor");

	ros::NodeHandle nh;

	// the results that will be published to the topic
	//bool labjackOk, kinectOk, abbOk;

	int timeThresh = 5; // Threshold for allowable time delay between topic publications, seconds

	// Topics that we want to watch for normal operation
	// TODO: Update These Topics
	// nh.param("labJackTopic", labJackTopic, labJackTopic)
	const string labJackTopic = "/AI0";
	const string kinectTopic = "/camera/rgb";
	const string abbTopic = "/";

	const string labJackParam = "/state/labjack_operating";
	const string kinectParam = "/state/kinect_operating";
	const string abbParam = "/state/abb_operating";

	// Listen to topics and run callback function for each
	nh.subscribe<Float32>(labJackTopic, 1, labjackCallback);

	
	// Set ROS Parameter accordingly
	// nh.setParam(labJackParam, labjackOK);
	// nh.setParam(kinectParam, kinectOK);
	// nh.setParam(abbParam, abbOK);
	
	// if(labjackOK && kinectOK && abbOK)
	// 	nh.setParam("/state/allSystemsNormal", TRUE);
	// else
	// 	nh.setParam("/state/allSystemsNormal", FALSE);


	ros::spin();
}

