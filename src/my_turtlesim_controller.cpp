#include "my_turtlesim_controller/my_turtlesim_controller.h"
#include <stdio.h>
MyTurtlesimController::MyTurtlesimController():private_nh("~")
{
    private_nh.param("hz",hz,{10});
    sub_pose = nh.subscribe("/turtle1/pose",10,&MyTurtlesimController::pose_callback,this);
    pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1);
}

void MyTurtlesimController::pose_callback(const turtlesim::Pose::ConstPtr &msg)
{
    current_pose = *msg;

}


void MyTurtlesimController::go_straight()
{
    // ROS_INFO_STREAM(current_pose.x);
    ROS_INFO_STREAM(current_pose.theta);

    geometry_msgs::Twist cmd_vel;
    // cmd_vel.linear.x = 1.0;
    cmd_vel.linear.y = 0;
    cmd_vel.angular.z = 0.1;
    pub_cmd_vel.publish(cmd_vel);
}



void MyTurtlesimController::process()
{
    ros::Rate loop_rate(hz);

    while(ros::ok())
    {
        go_straight();
        ros::spinOnce();
        loop_rate.sleep();
    }

}


int main(int argc,char** argv)
{
    ros::init(argc,argv,"my_turtlesim_controller");
    MyTurtlesimController my_turtlesim_controller;
    my_turtlesim_controller.process();
    return 0;
}
