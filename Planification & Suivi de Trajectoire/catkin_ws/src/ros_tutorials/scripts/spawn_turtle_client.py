#!/usr/bin/env python3

import rospy
from std_srvs.srv import Trigger

def spawn_turtle_client():
    # Initialiser le nœud ROS
    rospy.init_node('spawn_turtle_client', anonymous=True)

    # Attendre que le service '/spawn_turtle' soit disponible
    rospy.wait_for_service('/spawn_turtle')

    try:
        # Appeler le service '/spawn_turtle'
        spawn_turtle = rospy.ServiceProxy('/spawn_turtle', Trigger)
        response = spawn_turtle()

        # Afficher le message de réponse
        if response.success:
            rospy.loginfo(f"Service call successful: {response.message}")
        else:
            rospy.logwarn(f"Service call failed: {response.message}")
    except rospy.ServiceException as e:
        rospy.logerr(f"Service call failed: {e}")

if __name__ == '__main__':
    try:
        spawn_turtle_client()
    except rospy.ROSInterruptException:
        pass

