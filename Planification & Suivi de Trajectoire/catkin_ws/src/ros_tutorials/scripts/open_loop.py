#!/usr/bin/env python3
 
import rospy
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
 
class OpenLoopTurtleBot3:
    def __init__(self):
        # Initialisation du nœud ROS
        rospy.init_node('open_loop_turtlebot3', anonymous=True)
 
        # Publisher pour le topic /cmd_vel
        self.cmd_vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
 
        # Subscriber pour le topic /odom pour suivre la position réelle du robot
        self.odom_sub = rospy.Subscriber('/odom', Odometry, self.update_pose)
 
        # Position actuelle du robot
        self.current_x = 0.0
        self.target_distance = 6.0  # mètres
        self.linear_velocity = 0.3  # m/s
        self.tolerance = 0.05  # tolérance pour l'arrêt
 
        rospy.loginfo("Initialisation terminée. En attente du démarrage...")
 
    def update_pose(self, data):
        """Callback pour mettre à jour la position du robot à partir de /odom."""
        self.current_x = data.pose.pose.position.x
 
    def move_forward(self):
        rospy.loginfo("Démarrage du mouvement en avant...")
        rate = rospy.Rate(10)  # boucle à 10 Hz
 
        # Commande de vitesse initiale
        vel_msg = Twist()
        vel_msg.linear.x = self.linear_velocity
        vel_msg.angular.z = 0.0
 
        while not rospy.is_shutdown():
            # Vérification de la distance parcourue
            if self.current_x >= self.target_distance - self.tolerance:
                rospy.loginfo(f"Target position reached! Current position: x = {self.current_x:.2f} m")
                break
 
            # Publier la commande pour avancer
            self.cmd_vel_pub.publish(vel_msg)
            rospy.loginfo(f"Moving forward... Current position: x = {self.current_x:.2f} m")
            rate.sleep()
 
        # Arrêter le robot après avoir atteint la cible
        self.stop_robot()
 
    def stop_robot(self):
        rospy.loginfo("Arrêt du robot.")
        stop_msg = Twist()  # Commande de vitesse nulle pour arrêter
        self.cmd_vel_pub.publish(stop_msg)
 
if __name__ == '__main__':
    try:
        controller = OpenLoopTurtleBot3()
        rospy.sleep(2)  # Attendre que Gazebo initialise correctement la simulation
        controller.move_forward()
    except rospy.ROSInterruptException:
        pass
