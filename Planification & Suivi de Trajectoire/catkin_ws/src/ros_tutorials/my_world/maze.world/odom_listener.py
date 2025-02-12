#!/usr/bin/env python3
 
import rospy
from nav_msgs.msg import Odometry
import tf.transformations
 
def odom_callback(data):
    global last_time
    current_time = rospy.Time.now()
    time_diff = (current_time - last_time).to_sec()
 
    # Afficher les informations toutes les 2 secondes
    if time_diff >= 2.0:
        position = data.pose.pose.position
        orientation = data.pose.pose.orientation
        orientation_list = [orientation.x, orientation.y, orientation.z, orientation.w]
        euler = tf.transformations.euler_from_quaternion(orientation_list)
 
        rospy.loginfo(f"Position - x: {position.x}, y: {position.y}, z: {position.z}")
        rospy.loginfo(f"Orientation - Roll: {euler[0]}, Pitch: {euler[1]}, Yaw: {euler[2]}")
 
        last_time = current_time
 
def listener():
    global last_time
 
    rospy.init_node('odom_listener', anonymous=True)
    last_time = rospy.Time.now()
    rospy.Subscriber('/odom', Odometry, odom_callback)
    rospy.spin()
 
if __name__ == '__main__':
    listener()
