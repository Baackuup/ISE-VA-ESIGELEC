#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose

# Position cible
target_x = 9.0
target_y = 5.5

# Fonction de rappel pour surveiller la position actuelle de la tortue
def pose_callback(pose):
    global reached_goal
    if pose.x >= target_x:  # Vérifier si la position x est atteinte
        reached_goal = True

def move_to_goal():
    global reached_goal
    reached_goal = False

    # Initialiser le nœud ROS
    rospy.init_node('move_turtlesim_node2', anonymous=True)

    # Créer un éditeur pour le topic '/turtle1/cmd_vel'
    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)

    # Créer un abonné pour surveiller la position de la tortue
    rospy.Subscriber('/turtle1/pose', Pose, pose_callback)

    # Définir la fréquence de publication (10 Hz)
    rate = rospy.Rate(10)

    # Créer un message Twist pour le mouvement
    vel_msg = Twist()
    vel_msg.linear.x = 1.0  # Vitesse linéaire pour avancer

    while not rospy.is_shutdown():
        if not reached_goal:
            # Publier les commandes de vitesse pour avancer
            pub.publish(vel_msg)
        else:
            # Arrêter le robot après avoir atteint la cible
            vel_msg.linear.x = 0.0
            pub.publish(vel_msg)
            rospy.loginfo("Arrived !")
            break

        # Attendre jusqu'au prochain cycle
        rate.sleep()

if __name__ == '__main__':
    try:
        move_to_goal()
    except rospy.ROSInterruptException:
        pass

