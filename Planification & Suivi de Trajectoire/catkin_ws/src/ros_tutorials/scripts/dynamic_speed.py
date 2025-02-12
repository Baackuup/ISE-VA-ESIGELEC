#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist

def adjust_speed(msg):
    """
    Fonction de rappel qui ajuste les vitesses de la tortue en fonction des paramètres ROS.
    """
    # Lire les facteurs de vitesse depuis les paramètres ROS
    linear_speed_factor = rospy.get_param('/linear_speed_factor', 1.0)
    angular_speed_factor = rospy.get_param('/angular_speed_factor', 1.0)

    # Ajuster les vitesses linéaire et angulaire
    adjusted_msg = Twist()
    adjusted_msg.linear.x = msg.linear.x * linear_speed_factor
    adjusted_msg.angular.z = msg.angular.z * angular_speed_factor

    # Publier les vitesses ajustées
    pub.publish(adjusted_msg)

def dynamic_speed():
    """
    Initialise le nœud ROS pour ajuster dynamiquement les vitesses de la tortue.
    """
    rospy.init_node('dynamic_speed', anonymous=True)

    # Créer un abonné au topic /turtle1/cmd_vel
    rospy.Subscriber('/turtle1/cmd_vel', Twist, adjust_speed)

    # Garder le nœud actif
    rospy.spin()

if __name__ == '__main__':
    # Créer un éditeur pour publier sur /turtle1/cmd_vel
    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)
    
    try:
        dynamic_speed()
    except rospy.ROSInterruptException:
        pass

