/**
 *  MIT License
 *
 *  Copyright (c) 2019 Kamakshi Jain
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without
 *  limitation the rights to use, copy, modify, merge, publish, distribute,
 *  sublicense, and/or sell copies of the Software, and to permit persons to
 *  whom the Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be included
 *  in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 *  @file    main.cpp
 *  @author  Kamakshi Jain
 *  @copyright MIT License
 *
 *  @brief  class definition of WalkerAlgorithm class.
 *
 *  @section DESCRIPTION
 *
 *  This program is a main file for the walker algorithm. 
 *
 */
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
