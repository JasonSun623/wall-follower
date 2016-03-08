#ifndef HIGH_LEVEL_CONTROL_H
#define HIGH_LEVEL_CONTROL_H

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

/**
 * @brief Breaks down abstract movement commands into smaller ones,
 * that can be executed by the Low Level Control
 *
 * Usage:
 *     HighLevelControl high_level_control;
 *     high_level_control.FollowWallMove();
 *
 * @author Rubin Deliallisi
 * @date March 2016
 */
class HighLevelControl {

private:

    // TODO(rdeliallisi): To be put into Low Level Control
    /**
     * Ros node to which the class is attached
    */
    ros::NodeHandle node_;

    // TODO(rdeliallisi): To be put into Low Level Control
    /**
     * Used to send messages to the actual robot
     */
    ros::Publisher cmd_vel_pub_;

    // TODO(rdeliallisi): To be put into Object Detection
    /**
     * Used to get the data from the laser range finder
     */
    ros::Subscriber laser_sub_;

    /**
     * The type of turn the robot is currently in when turning.
     */
    int turn_type_;

    /**
     * Minimum proximity distance that the robot can have from a wall
     */
    double security_distance_;

    /**
     * Maximum distance the robot can be away from the anchor wall
     */
    double wall_follow_distance_;

    double linear_velocity_;

    double angular_velocity_;

    /**
     * Can the robot continue walking in a straight line or not
     */
    bool can_continue_;

    /**
     * Is the robot close enough to the anchor wall
     */
    bool is_close_to_wall_;

    /**
     * Is the robot anchored to a wall or not
     */
    bool is_following_wall_;

    bool is_turning_;

    // TODO(rdeliallisi): To be put into Object Detection
    /**
     * Gets the data from the laser range finder, examines them and
     * updates the relevant class variables
     * @param msg Raw data comming from the laser range finder
     */
    void LaserCallback(const sensor_msgs::LaserScan::ConstPtr& msg);

    //TODO(rdeliallisi): To be put into Low Level Control
    /**
     * Send the movement command to the robot using ROS nodes and
     * topics
     * @param linear_speed  Linear Speed that the robot should move with
     * @param angular_speed Angular Speed that the robot should rotate with
     */
    void Move(double linear_speed, double angular_speed);

public:
    HighLevelControl();

    /**
     * Change the minimum distance the robot can be close to the wall to
     * @param security_distance New security distance of the robot
     */
    void set_security_distance(double security_distance);

    /**
     * Change the angular velocity of the robot
     * @param angular_velocity New angular velocity of the robot
     */
    void set_angular_velocity(double angular_velocity);

    /**
     * Change the angular velocity of the robot
     * @param linear_velocity New angular velocity of the robot
     */
    void set_linear_velocity(double linear_velocity);


    /**
     * Override method for testing purposes
     * @param turn_type Decides the type of the wall the robot is following.
     * 1 for right wall, -1 for left wall
     */
    void set_turn_type(int turn_type);

    /**
     * Checks if the robot can continue waking forward or not
     * @return Returns the value of can_continue_
     */
    bool can_continue() {
        return can_continue_;
    }

    /**
     * Checks if the robot is close enough to the wall it is anchored to 
     * @return Returns the value of is_close_to_wall_
     */
    bool is_close_to_wall() {
        return is_close_to_wall_;
    }

    /**
     * Checks if the robot is anchored and following a specific wall
     * @return Returns the value of is_following_wall_
     */
    bool is_following_wall() {
        return is_following_wall_;
    }

    /**
     * Checks if the robot is in the middle of a turning process
     * @return Returns the value of is_turning_
     */
    bool is_turning() {
        return is_turning_;
    }

    /**
     * Moves the robot so that it always follows a wall
     */
    void WallFollowMove();

    /**
     * Moves the robot randomly using the specified linear and
     * angular velocity. The robot will chose a direction to turn and
     * turn in that direction until it completes the turn.
     */
    void ControlledRandomMove();

    /**
     * Turns the robot a random amount of degrees in a random direction each
     * time an obstacle is encountered.
     */
    void TotalRandomMove();
};

#endif