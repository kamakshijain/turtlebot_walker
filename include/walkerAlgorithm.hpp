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
 *  @brief  This is a hpp file for walkerAlgorithm.cpp
 *
 *  @section DESCRIPTION
 *
 *  This program is a main file for the walker algorithm. 
 *
 */

#ifndef TURTLEBOT_WALKER_INCLUDE_WALKERALGORITHM_HPP_
#define TURTLEBOT_WALKER_INCLUDE_WALKERALGORITHM_HPP_

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

/**
 * @brief Class for the Walker Algorith.
 */

class WalkerAlgorithm {
 private:
  // Declare private variables and methods
  bool obstacle_flag;  /// Declare a variable to detect poosible collision

  geometry_msgs::Twist msg;  /// Declare a variable for publishing velocity.

  ros::NodeHandle nh;  /// Create a node handle

  // Create a publisher that publishes to velocity topic.
  ros::Publisher publishVelocity;

  // Create a subscriber that subscribes to laserscan topic
  ros::Subscriber subscribeLaserScan;

 public:
  /**
   * @brief Constructor for Walker_algorithm class.
   */
  WalkerAlgorithm();
   /*
   * @brief Destuctor for Walker_algorithm class.
   */
  ~WalkerAlgorithm();

   /**
   * @brief Callback function for laser scanner of walker
   */
  void laserScannerCallback(const sensor_msgs::LaserScan::ConstPtr& input);

   /**
   * @brief Method to check obstacles
   * 
   * @return bool 1 if robot near obtacle, 0 otherwise. 
   */
  bool checkObstacle();

   /** 
   * @brief Method to run the robot.
   */
  void runTurtlebot();
};

#endif  // TURTLEBOT_WALKER_INCLUDE_WALKERALGORITHM_HPP_
