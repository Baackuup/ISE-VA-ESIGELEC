#!/usr/bin/env python3
 
import rospy
import tf2_ros
from geometry_msgs.msg import TransformStamped
import tf.transformations
 
def listener():
    rospy.init_node('tf_listener')
 
    tfBuffer = tf2_ros.Buffer()
    listener = tf2_ros.TransformListener(tfBuffer)
 
    rate = rospy.Rate(0.5)  # toutes les 2s
    while not rospy.is_shutdown():
        try:
            trans = tfBuffer.lookup_transform('odom', 'base_footprint', rospy.Time())
            position = trans.transform.translation
            orientation = trans.transform.rotation
            orientation_list = [orientation.x, orientation.y, orientation.z, orientation.w]
            euler = tf.transformations.euler_from_quaternion(orientation_list)
 
            rospy.loginfo(f"Position - x: {position.x}, y: {position.y}, z: {position.z}")
            rospy.loginfo(f"Orientation - Roll: {euler[0]}, Pitch: {euler[1]}, Yaw: {euler[2]}")
 
        except (tf2_ros.LookupException, tf2_ros.ConnectivityException, tf2_ros.ExtrapolationException) as e:
            rospy.logwarn(f"Transformation error: {e}")
            continue
 
        rate.sleep()
 
if __name__ == '__main__':
    listener()
