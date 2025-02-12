#!/usr/bin/env python3

import rospy
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Quaternion
import tf
from tf.transformations import euler_from_quaternion

def odom_callback(msg):
    """
    Callback pour extraire et afficher la position et l'orientation du robot depuis /odom
    """
    # Extraire la position (x, y, z)
    position = msg.pose.pose.position
    rospy.loginfo(f"Position from /odom: x = {position.x}, y = {position.y}, z = {position.z}")

    # Extraire l'orientation sous forme de quaternion
    orientation = msg.pose.pose.orientation
    # Convertir le quaternion en angles d'Euler
    euler = euler_from_quaternion([orientation.x, orientation.y, orientation.z, orientation.w])

    rospy.loginfo(f"Orientation from /odom: roll = {euler[0]}, pitch = {euler[1]}, yaw = {euler[2]}")

def tf_listener():
    """
    Fonction pour écouter les transformations entre 'odom' et 'base_link' et afficher les coordonnées et orientation
    """
    rospy.init_node('turtlebot_pose_comparison', anonymous=True)
    listener = tf.TransformListener()

    rate = rospy.Rate(10)  # 10 Hz

    while not rospy.is_shutdown():
        try:
            # Attendre la transformation entre les frames odom et base_link
            listener.waitForTransform('odom', 'base_link', rospy.Time(0), rospy.Duration(1.0))

            # Obtenir la transformation
            (trans, rot) = listener.lookupTransform('odom', 'base_link', rospy.Time(0))

            # Afficher la position (x, y, z)
            rospy.loginfo(f"Position from TF: x = {trans[0]}, y = {trans[1]}, z = {trans[2]}")

            # Convertir le quaternion en angles d'Euler
            euler = euler_from_quaternion(rot)
            rospy.loginfo(f"Orientation from TF: roll = {euler[0]}, pitch = {euler[1]}, yaw = {euler[2]}")

        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException) as e:
            rospy.logwarn("TF Exception: %s", e)

        rate.sleep()

def main():
    rospy.init_node('turtlebot3_pose_comparator', anonymous=True)

    # Méthode 1 : S'abonner à /odom
    rospy.Subscriber('/odom', Odometry, odom_callback)

    # Méthode 2 : Utiliser le listener pour obtenir les transformations
    tf_listener()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass

