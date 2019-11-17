# Turtlebot Walker

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Project Overview

This repository includes a package for turtlebot to implement a simple walker algorithm much like Roomba robot vacuum cleaner. The robot moves straight until it comes near to the obstacle. When it is near the obstacle, it rotates on its place until the way ahead is clear. It uses the laser scan published data to check for obstruction in its path to avoid it.

## Dependencies 
The dependencies of this repository are:
 ```
* Ubuntu 16.04
* ROS Kinetic
* Gazebo
* Turtlebot_Gazebo package
```

To install ROS, follow the instructions on this [link](http://wiki.ros.org/kinetic/Installation)

>Note: Gazebo & Rviz will be already installed as part of the ROS distro, however, Turtlebot_Gazebo needs to be installed separately.

To install turtlebot_Gazebo, open a terminal and run the following command: 

```
$ sudo apt-get install ros-kinetic-turtlebot-gazebo ros-kinetic-turtlebot-apps ros-kinetic-turtlebot-rviz-launchers
```

## Building Instructions
```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/
catkin_make
source devel/setup.bash
cd src/
git clone --recursive https://github.com/kamakshijain/turtlebot_walker.git
cd ~/catkin_ws
catkin_make
```

## Running the code using rosrun

After following the installation instructions above, you can run the gazebo system and walker node separately by following the below commands. Make sure your current directory is ``` ~/catkin_ws/```

```
roslaunch turtlebot_gazebo turtlebot_world.launch
```

You will see a gazebo window open along with default turtlebot_world with obstacles as well as the turtlebot robot. Then run the walker ros node by running the command below in a new terminal.

```
cd ~/catkin_ws/
source devel/setup.bash
rosrun turtlebot_walker walker
```

In the Gazebo window, you will be able to see that the turtlebot starts running, and when it reaches near an obstacle, it starts turning until obstacle is clear. 

## Running the code using roslaunch 

Instead of running the code in different command windows using rosrun, you can also run all of them together using roslaunch by typing the following command in the terminal. It will start both walker node and turtlebot_gazebo world.

>Note: roscore launches automatically (if it is not running) after the following command is executed. 


```
cd ~/catkin_ws/
roslaunch turtlebot_walker walker.launch 
```

## Recording bag files with the launch file

You may run the command below to launch the nodes and record all the topics to a bag file. The bag file will be in the results/ directory once the recording is complete. By default it records for 30 seconds. 

```
roslaunch turtlebot_walker walker.launch record:=true
```

If you want to launch all the nodes without recording bag file, execute the following command. The default record argument is false. 

```
roslaunch turtlebot_walker walker.launch
```

## Playing back the bag file. 

First launch the turtlebot_gazebo world by typing the following command, then and play the bag file, thus instead of running the walker node we will use the information recorded in the bag file.

```
roslaunch turtlebot_gazebo turtlebot_world.launch
```

Now, navigate to the results subdirectory in the turtlebot_walker package in another terminal. And enter the command below while in the results subdirectory. 

```
rosbag play walker_record.bag
```
You can view all the messages being published on a topic e.g. ```/cmd_vel_mux/input/navi.```

```
rostopic echo /cmd_vel_mux/input/navi
```

