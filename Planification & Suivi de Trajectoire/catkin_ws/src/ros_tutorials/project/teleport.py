#!/usr/bin/env python3
 
import rospy
from gazebo_msgs.srv import SetModelState
from gazebo_msgs.msg import ModelState
 
def teleport_robot():
    rospy.init_node('teleport_robot', anonymous=True)
    rospy.wait_for_service('/gazebo/set_model_state')
    try:
        set_model_state = rospy.ServiceProxy('/gazebo/set_model_state', SetModelState)
        model_state = ModelState()
        model_state.model_name = 'turtlebot3_burger'  # Nom du modèle dans Gazebo
        model_state.pose.position.x = -1.0
        model_state.pose.position.y = 1.5
        model_state.pose.position.z = 0.0
        model_state.pose.orientation.x = 0.0
        model_state.pose.orientation.y = 0.0
        model_state.pose.orientation.z = 0.0
        model_state.pose.orientation.w = 1.0
        resp = set_model_state(model_state)
        if resp.success:
            rospy.loginfo("Robot téléporté avec succès aux coordonnées (x=-1, y=1.5)")
        else:
            rospy.loginfo("Échec de la téléportation du robot")
    except rospy.ServiceException as e:
        rospy.loginfo(f"Service call failed: {e}")
 
if __name__ == '__main__':
    try:
        teleport_robot()
    except rospy.ROSInterruptException:
        pass
