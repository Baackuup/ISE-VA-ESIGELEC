#!/usr/bin/env python3

import rospy
from std_srvs.srv import Empty

def reset_turtle_client():
    # Initialiser le nœud ROS
    rospy.init_node('reset_turtle_client', anonymous=True)

    # Attendre que le service '/reset_turtle' soit disponible
    rospy.wait_for_service('/reset_turtle')

    try:
        # Appeler le service '/reset_turtle'
        reset_turtle = rospy.ServiceProxy('/reset_turtle', Empty)
        reset_turtle()

        rospy.loginfo("Service call to reset turtle was successful.")
    except rospy.ServiceException as e:
        rospy.logerr(f"Service call failed: {e}")

if __name__ == '__main__':
    try:
        reset_turtle_client()
    except rospy.ROSInterruptException:
        pass
