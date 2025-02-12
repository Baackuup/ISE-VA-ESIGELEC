#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist

def record_turtle_motion():
    # Initialiser le nœud ROS
    rospy.init_node('record_turtle_motion', anonymous=True)

    # Créer un éditeur pour le topic /turtle1/cmd_vel
    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)

    # Définir la vitesse linéaire et angulaire pour la tortue
    move_cmd = Twist()
    move_cmd.linear.x = 1.0  # Vitesse linéaire de 1 m/s
    move_cmd.angular.z = 0.5  # Rotation de 0.5 rad/s

    # Définir la fréquence de publication (10 Hz)
    rate = rospy.Rate(10)

    # Publier les commandes de vitesse pendant 10 secondes
    rospy.loginfo("Starting to move turtle...")
    start_time = rospy.Time.now().to_sec()

    while rospy.Time.now().to_sec() - start_time < 10:
        pub.publish(move_cmd)
        rate.sleep()

    # Arrêter la tortue après 10 secondes
    move_cmd.linear.x = 0.0
    move_cmd.angular.z = 0.0
    pub.publish(move_cmd)
    rospy.loginfo("Turtle stopped.")

if __name__ == '__main__':
    try:
        record_turtle_motion()
    except rospy.ROSInterruptException:
        pass

