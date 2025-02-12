#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Pose
from gazebo_msgs.srv import SetModelState
from gazebo_msgs.msg import ModelState

def teleport_robot():
    rospy.init_node('teleport_turtlebot3', anonymous=True)

    # Attendre que le service de téléportation soit disponible
    rospy.wait_for_service('/gazebo/set_model_state')

    try:
        set_state = rospy.ServiceProxy('/gazebo/set_model_state', SetModelState)
        state_msg = ModelState()
        state_msg.model_name = 'turtlebot3_waffle'
        state_msg.pose.position.x = 2.0  # Nouvelle position X
        state_msg.pose.position.y = 2.0  # Nouvelle position Y
        state_msg.pose.position.z = 0.1  # Hauteur (fixe)
        state_msg.pose.orientation.w = 1.0  # Orientation neutre

        # Envoyer la commande de téléportation
        resp = set_state(state_msg)
        rospy.loginfo("TurtleBot3 téléporté avec succès.")
    except rospy.ServiceException as e:
        rospy.logerr(f"Erreur lors de la téléportation : {e}")

if __name__ == '__main__':
    try:
        teleport_robot()
    except rospy.ROSInterruptException:
        pass

