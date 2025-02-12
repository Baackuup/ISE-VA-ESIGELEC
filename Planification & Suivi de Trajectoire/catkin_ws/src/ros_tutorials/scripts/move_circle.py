#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist

def move_turtle_circle(duration):
    # node
    rospy.init_node('move_turtlesim_node1')

    # create a file
    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)

    # frequency
    rate = rospy.Rate(10)

    # message
    vel_msg = Twist()
    vel_msg.linear.x = 5.0  # linear
    vel_msg.angular.z = 5.0  # angular

    # time
    start_time = rospy.Time.now().to_sec()

    while not rospy.is_shutdown():
        current_time = rospy.Time.now().to_sec()
        elapsed_time = current_time - start_time

        # show speed and time
        if elapsed_time < duration:
            pub.publish(vel_msg)
        else:
            # stop the turtle
            vel_msg.linear.x = 0.0
            vel_msg.angular.z = 0.0
            pub.publish(vel_msg)
            break

        # wait
        rate.sleep()

if __name__ == '__main__':
    try:
        # tell the time
        move_turtle_circle(duration=5)
    except rospy.ROSInterruptException:
        pass

