#!/usr/bin/env python3
 
import rospy
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
import math
 
class GoToGoal:
    def __init__(self):
        # Initialize ROS node
        rospy.init_node('turtle_go_to_goal', anonymous=True)
 
        # Target position
        self.x_target = 1.0
        self.y_target = 1.0
 
        # Publisher for velocity commands
        self.cmd_vel_pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)
 
        # Subscriber for current pose
        self.pose_sub = rospy.Subscriber('/turtle1/pose', Pose, self.update_pose)
 
        # Current pose
        self.pose = Pose()
 
        # Tolerance for reaching the goal
        self.tolerance = 0.1
 
        # Rate for loop frequency
        self.rate = rospy.Rate(10)
 
    def update_pose(self, data):
        """Callback to update the pose."""
        self.pose = data
 
    def euclidean_distance(self):
        """Calculate the Euclidean distance to the target."""
        return math.sqrt((self.x_target - self.pose.x) ** 2 + (self.y_target - self.pose.y) ** 2)
 
    def linear_velocity(self, constant=1.5):
        """Calculate the linear velocity proportional to the distance."""
        return constant * self.euclidean_distance()
 
    def angular_velocity(self, constant=6.0):
        """Calculate the angular velocity proportional to the angle difference."""
        desired_angle = math.atan2(self.y_target - self.pose.y, self.x_target - self.pose.x)
        return constant * (desired_angle - self.pose.theta)
 
    def move_to_goal(self):
        """Move the turtle to the goal position."""
        vel_msg = Twist()
 
        while not rospy.is_shutdown():
            distance = self.euclidean_distance()
 
            # Check if the turtle reached the target
            if distance < self.tolerance:
                rospy.loginfo("Reached target position!")
                vel_msg.linear.x = 0
                vel_msg.angular.z = 0
                self.cmd_vel_pub.publish(vel_msg)
                break
 
            # Set velocities
            vel_msg.linear.x = self.linear_velocity()
            vel_msg.angular.z = self.angular_velocity()
 
            # Publish the velocities
            self.cmd_vel_pub.publish(vel_msg)
            rospy.loginfo(f"Moving towards target: distance={distance:.2f}")
 
            # Sleep to maintain rate
            self.rate.sleep()
 
if __name__ == '__main__':
    try:
        turtle = GoToGoal()
        turtle.move_to_goal()
    except rospy.ROSInterruptException:
        pass
