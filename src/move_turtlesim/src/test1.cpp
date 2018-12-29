// Code: Test1.
// Objective: Simulate the movement of a Turtlebot usin Turtlesim as basis for a further code using Turttlebot hardware.
// Mini project.
// Author: Team C2-05, Robot Programming, Robotics, AAU.
// December 2018.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Summary: The code shows two options to work. The first one generates random movements for the turtle and tracks the coordinates at every movement.
// An area is delimited and if the movement commanded to the turtle makes it go further than the dimensions established, the turtle will avoid the instruction and take the next one.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include<stdlib.h>                    //used to generate random numbers
#include<time.h>                      //used to generate random numbers
#include<math.h>                      //used to get sin and cos functions
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
int randvel(){                        // This function type integer is used to generate a random value for the linear displacement of the turtle between 5 and 1.
  int vel=0;
  vel=1+rand()%(6-1);
  return vel;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int randrot(){                        // This function type integer is used to generate a random value for the angular displacement of the turtle between 3 and -3 radians.
  int rot=0;
  rot=1+rand()%(7)-3;//
  return rot;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void movefunc(){                      // This function moves the turtlebot through random directions and tracks its position.
  double angle=0;                     // This variable will be actualized for every movement.
  double realangle=0;                 // This variable will keep track of the turtle's angle seen from the very initial position
  double posx=0;                      // This variable will keep track of the displacement in X-axis at every movement.
  double posy=0;                      // This variable will keep track of the displacement in Y-axis at every movement.
  double ahead=0;                     // This variable will dictate the distance of each linear movement.
  double realposx=0;                  // This variable will keep track of the displacement in X-axis seen from the origin.
  double realposy=0;                  // This variable will keep track of the displacement in Y-axis seen from the origin.
  int rep=0;
  cout << "How many repetitions do you want?"<<endl; //The user is asked how many repetitions are required, 1 repetition include 1 rotation and one displacement.
  cin>>rep;
  ros::NodeHandle nh;
  ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);  //It is advertisedd that the publisher will publish in the cmd_vel topic (the turtle simulator is subscribed to this topic)
  for (int i=0;i<rep;i++){
    ros::Duration(1.0).sleep();
    geometry_msgs::Twist msg;
    msg.linear.x = 0.0;
    angle=randrot();                          // The variable angle gets a value from the function randrot()
    realangle=realangle+angle;//              // The value of the angle seen from the origin is updated each cycle.
    msg.angular.z = angle;                    // First a rotation is performed.
    cmd_vel_pub.publish(msg);                 // The message is published to the topic.
    ros::Duration(1.0).sleep();
    ahead = randvel();                        // Now the variable ahead gets a value from the fucntion randvel() to indicate a linear displacement.
    posx=ahead*cos(realangle);                // The X and Y components of every linear movement are calculated.
    posy=ahead*sin(realangle);
    if (realposx+posx<5&&realposx+posx>(-5)) {  //This two conditions check if the next movement will keep the turtle inside the area indicated.
      if (realposy+posy<5&&realposy+posy>(-5)) { // If the longitude of the next movement is enough to get the turtle out of the area, the instruction is avoided.
    realposx=realposx+posx;                     // The components in X and Y axis are added every cycle.
    realposy=realposy+posy;
    msg.linear.x = ahead;
    msg.angular.z = 0.0;
    cout<<"position en X: "<<realposx<<endl;
    cout<<"position en Y: "<<realposy<<endl;
    cmd_vel_pub.publish(msg);
  }
  else {
    cout<<"The position in Y would be: "<<realposy+posy<<", limit is -+5"<<endl;
  }
  }
  else {
    cout<<"The position in X would be: "<<realposx+posx<<", limit is -+5"<< endl;
  }
  }

}
///////////////////////////////////////////////////////////////////////
void rotatefunc(){                              //This function is written in order to test only the rotatory movement of the simulation. No return value is required.
  double value = 0.0;

  cout<<"How many radians?"<<endl;
  cin>>value;
  ros::NodeHandle nh;
  ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
  ros::Duration(1.0).sleep();
  geometry_msgs::Twist msg;
  msg.linear.x = 0.0;
  msg.angular.z = value;
  cmd_vel_pub.publish(msg);
  ros::Duration(1.0).sleep();

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) { //Main function that contains only 2 cases to be selected. Every case calls a function.
  int method=0;
  srand(time(NULL));
  ros::init(argc, argv, "move_turtlesim");
  cout<<"Which working method do you prefer? 1. Move or 2. Rotate"<<endl;
  cin>>method;
  switch (method) {
    case 1:
      movefunc();
    break;

  case 2:
    rotatefunc();
  break;
}
  ros::spin();
  return 0;
}
