#!/usr/bin/env python3
import rospy
import tf
from turtlesim.msg import Pose
from geometry_msgs.msg import TransformStamped
 
def handle_turtle1_pose(msg):
    br = tf.TransformBroadcaster()
    br.sendTransform((msg.x, msg.y, 0),
                     tf.transformations.quaternion_from_euler(0, 0, msg.theta),
                     rospy.Time.now(),
                     "turtle1",
                     "world")
 
if __name__ == '__main__':
    rospy.init_node('turtle1_tf_broadcaster')
    rospy.Subscriber('/turtle1/pose', Pose, handle_turtle1_pose)
    rospy.spin()
