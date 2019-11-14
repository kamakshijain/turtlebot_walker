#include "walkerAlgorithm.hpp"

/**
 * @brief      main function
 *
 * @param[in]  argc  The argc
 * @param      argv  The argv
 *
 * @return     nothing
 */

int main(int argc, char* argv[]) {
    //Initialize the ROS node
    ros::init(argc, argv, "walkerAlgorithm");

     //Create the object for class walkerAlgorithm
    WalkerAlgorithm walker;

     // Implement the walker behaviour 
    walker.runTurtlebot();

    return 0;
}
