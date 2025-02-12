#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist
import time

def move_robot():
    rospy.init_node('control_turtlebot3', anonymous=True)
    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    vel_msg = Twist()

    rate = rospy.Rate(1)

    # Avancer
    vel_msg.linear.x = 0.5
    vel_msg.angular.z = 0.0
    rospy.loginfo("Avancer")
    pub.publish(vel_msg)
    time.sleep(2)

    # S'arrêter
    vel_msg.linear.x = 0.0
    vel_msg.angular.z = 0.0
    rospy.loginfo("S'arrêter")
    pub.publish(vel_msg)
    time.sleep(1)

    # Tourner dans le sens des aiguilles d'une montre
    vel_msg.linear.x = 0.0
    vel_msg.angular.z = -0.5
    rospy.loginfo("Tourner dans le sens des aiguilles d'une montre")
    pub.publish(vel_msg)
    time.sleep(2)

    # Tourner dans le sens inverse des aiguilles d'une montre
    vel_msg.angular.z = 0.5
    rospy.loginfo("Tourner dans le sens inverse des aiguilles d'une montre")
    pub.publish(vel_msg)
    time.sleep(2)

    # S'arrêter
    vel_msg.linear.x = 0.0
    vel_msg.angular.z = 0.0
    rospy.loginfo("S'arrêter")
    pub.publish(vel_msg)

if __name__ == '__main__':
    try:
        move_robot()
    except rospy.ROSInterruptException:
        pass

