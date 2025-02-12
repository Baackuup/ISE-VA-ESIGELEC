#!/usr/bin/env python3

import rospy
from std_srvs.srv import Empty

# Fonction de gestion pour le service '/reset_turtle'
def handle_reset_turtle(req):
    try:
        # Appeler le service '/reset' pour réinitialiser la position de la tortue
        rospy.wait_for_service('/reset')
        reset_turtle = rospy.ServiceProxy('/reset', Empty)
        reset_turtle()

        # Appeler le service '/clear' pour nettoyer la toile
        rospy.wait_for_service('/clear')
        clear_canvas = rospy.ServiceProxy('/clear', Empty)
        clear_canvas()

        rospy.loginfo("Turtle successfully reset and canvas cleared.")
        return []
    except Exception as e:
        rospy.logerr(f"Failed to reset turtle: {e}")
        return []

def reset_turtle_service():
    # Initialiser le nœud ROS
    rospy.init_node('reset_turtle_service', anonymous=True)

    # Créer un serveur de service pour '/reset_turtle'
    service = rospy.Service('/reset_turtle', Empty, handle_reset_turtle)

    rospy.loginfo("Reset turtle service is ready.")
    rospy.spin()

if __name__ == '__main__':
    try:
        reset_turtle_service()
    except rospy.ROSInterruptException:
        pass
