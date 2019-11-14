#ifndef INCLUDE_WALKERALGORITHM_HPP_
#define INCLUDE_WALKERALGORITHM_HPP_
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

/**
 * @brief Class for the Walker Algorith.
 */

class WalkerAlgorithm {
 private:
  //Declare private variables and methods
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

#endif  // INCLUDE_WALKERALGORITHM_HPP_
