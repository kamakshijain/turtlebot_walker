#include "walkerAlgorithm.hpp"

/**
 * @brief      Constructs the object.
 */
WalkerAlgorithm::WalkerAlgorithm() {
    // initialise the obstacle flag to be false
    obstacle_flag = false;
    // Publish the velocity to cmd_vel_mux/input/navi
    publishVelocity = nh.advertise <geometry_msgs::Twist> ("/cmd_vel_mux/input/navi",
    1000);
    // Subcribe to the /scan topic and use the laserCallback method
    subscribeLaserScan = nh.subscribe <sensor_msgs::LaserScan> ("/scan", 500,
                                &WalkerAlgorithm::laserScannerCallback, this);
    // Define the initial velocity message
    msg.linear.x = 0.0;
    msg.linear.y = 0.0;
    msg.linear.z = 0.0;
    msg.angular.x = 0.0;
    msg.angular.y = 0.0;
    msg.angular.z = 0.0;
    // stop the turtlebot
    publishVelocity.publish(msg);
}

/**
 * @brief      Destroys the object.
 */
WalkerAlgorithm::~WalkerAlgorithm() {
    // Stop the turtlebot before exiting
    msg.linear.x = 0.0;
    msg.linear.y = 0.0;
    msg.linear.z = 0.0;
    msg.angular.x = 0.0;
    msg.angular.y = 0.0;
    msg.angular.z = 0.0;
    // stop the turtlebot
    publishVelocity.publish(msg);
}

void WalkerAlgorithm::laserScannerCallback(cont sensor_msgs::LaserScan::ConstPtr& input) {
void WalkerAlgorithm::laserScannerCallback(const sensor_msgs::LaserScan::ConstPtr& input) {
    double safe_distance = 0.75;
    for (int i = 0; i < input->ranges.size(); ++i) {
        if (input->ranges[i] < safe_distance) {
        obstacle_flag = true;
        return;
        }
    }
    obstacle_flag = false;
}

bool WalkerAlgorithm::checkObstacle() {
    return obstacle_flag;
}

void WalkerAlgorithm::runTurtlebot() {
    // Set the frequency of publisher
    ros::Rate loop_rate(10);

     //Keep running till ROS is running fine. 
    while (ros::ok()) {
        // Proceed if obstacle encountered. 
        if(checkObstacle()) {
            ROS_INFO_STREAM("Obstacle Detected...!!!");
            // Turn the robot 
            msg.linear.x = 0.0;
            msg.angular.z = 1.0;
        } else {
            ROS_INFO_STREAM("Going Straight");
            msg.linear.x = 0.1;
            msg.angular.z = 0.0;
        }

        // Publish the message 
        publishVelocity.publish(msg);

        // "Spin" a callback in case we setup any callbacks 
        ros::spinOnce();

         //Sleep untill we reach time for 10Hz rate.
        loop_rate.sleep();
    }
}
