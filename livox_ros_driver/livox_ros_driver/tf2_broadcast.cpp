// #include <ros/ros.h>
// #include <tf2_ros/transform_broadcaster.h>
// #include <geometry_msgs/TransformStamped.h>

#include <ros/ros.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <cstdio>
#include <tf2/LinearMath/Quaternion.h>

std::string static_livox_name;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "my_static_tf2_broadcaster");
    if (argc != 8)
    {
        ROS_ERROR("Invalid number of parameters\nusage: static_tf2_broadcaster child_frame_name x y z roll pitch yaw");
        return -1;
    }
    if (strcmp(argv[1], "world") == 0)
    {
        ROS_ERROR("Static tf cannot be named 'world'");
        return -1;
    }
    static_livox_name = argv[1];
    static tf2_ros::StaticTransformBroadcaster static_broadcaster;
    // Create a TransformStamped message
    geometry_msgs::TransformStamped transformStamped;
    transformStamped.header.stamp = ros::Time::now();    // Set the timestamp
    transformStamped.header.frame_id = "world";          // Parent frame ID
    transformStamped.child_frame_id = static_livox_name; // Child frame ID

    // Set the transformation (position and orientation)
    transformStamped.transform.translation.x = atof(argv[2]);
    transformStamped.transform.translation.y = atof(argv[3]);
    transformStamped.transform.translation.z = atof(argv[4]);

    tf2::Quaternion quat;
    quat.setRPY(atof(argv[5]), atof(argv[6]), atof(argv[7]));

    transformStamped.transform.rotation.x = quat.x();
    transformStamped.transform.rotation.y = quat.y();
    transformStamped.transform.rotation.z = quat.z();
    transformStamped.transform.rotation.w = quat.w();

    // Publish the TF
    static_broadcaster.sendTransform(transformStamped);
    ROS_INFO("Spinning until killed publishing %s to world", static_livox_name.c_str());
    ros::spin();
    return 0;
}
