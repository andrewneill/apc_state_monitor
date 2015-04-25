/*
System monitor for the CSM Amazon Picking Challenge
Team Blaster

created 4/23/2015 by Andrew Neill (aneill@mines.edu)
last update 4/23/2015 Andrew Neill

Few items to review:
1. What topics are we listening to?
2. What message format are they in?

*/

#include <ros/ros.h>
#include <message_event.h>

class stateMonitor
{
public:
	stateMonitor();

private:
	ros::NodeHandle nh;

	// the results that will be published to the topic
	bool labjackOk, kinectOk, abbOk;

	// Topics that we want to watch for normal operation
	// TODO: Update These Topics
	static const string labJackTopic = "/";
	static const string kinectTopic = "/camera/rgb";
	static const string abbTopic = "/";

	static const string labJackParam = "/state/labjack_operating";
	static const string kinectParam = "/state/kinect_operating";
	static const string abbParam = "/state/abb_operating";

	// Subscriber node handle -> switched to message event
	//ros::Subscriber state_sub;
	// See section 2.4 of : http://wiki.ros.org/roscpp/Overview/Publishers%20and%20Subscribers
	ros::MessageEvent state_event;
};


// See section 2.4 of : http://wiki.ros.org/roscpp/Overview/Publishers%20and%20Subscribers
void callback(const ros::MessageEvent<std_msgs::String const>& event)
{
  const std::string& publisher_name = event.getPublisherName();
  const ros::M_string& header = event.getConnectionHeader();
  ros::Time receipt_time = event.getReceiptTime();

  const std_msgs::StringConstPtr& msg = event.getMessage();
}
// but is this just listening to any topic or how do I specify a specific topic?






stateMonitor::stateMonitor()
{
	
	// Check state of topic
	// TODO: check message type for these
	sensor_msgs::voltage


	// Set ROS Parameter accordingly
	nh.setParam(labJackParam, labjackOK);
	nh.setParam(kinectParam, kinectOK);
	nh.setParam(abbParam, abbOK);
	
	if(labjackOK && kinectOK && abbOK)
		nh.setParam("/state/allSystemsNormal", TRUE);
	else
		nh.setParam("/state/allSystemsNormal", FALSE);

}



int main(int argc, char** argv)
{
	ros::init(argc, argv, "apc_state_monitor");
	stateMonitor apc_state_monitor;

	ros::spin();
}

