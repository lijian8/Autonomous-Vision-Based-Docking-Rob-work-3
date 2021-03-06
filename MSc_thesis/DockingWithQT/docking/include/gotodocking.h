#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
//#include "user_marker.h"

#include <interactive_markers/interactive_marker_server.h>
#include <interactive_markers/menu_handler.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <math.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> Client;

class GoToDocking
{

public:

	const static double FORWARD_SPEED_MPS = .1;
	const static double MIN_SCAN_ANGLE_RAD = -30/180*M_PI;
	const static double MAX_SCAN_ANGLE_RAD = 30/180*M_PI;
	const static float MIN_PROXIMITY_RANGE_M = .5;
	
	//constructor
	GoToDocking();
	
	void RobotGoTo(double xPos, double yPos, double zPos,
                                 double wOrien, double xOrien, double yOrien,
                                 double zOrien);
	
private:

	ros::NodeHandle node;
	ros::Publisher commandPub;
	ros::Publisher commandPubP;
	ros::Publisher commandPubM;
	ros::Subscriber laserSubF;
	ros::Subscriber laserSubR;
	
        Client ac;
	
	bool keepMoving;
	
	void MoveForward();
	
	void MoveDesiredLoc(double xPos, double yPos, double zPos,
                                 double wOrien, double xOrien, double yOrien,
                                 double zOrien);
	
	void ScanCallBackF(const sensor_msgs::LaserScan::ConstPtr& scanF);

        void ScanCallBackR(const sensor_msgs::LaserScan::ConstPtr& scanR);
           
};
