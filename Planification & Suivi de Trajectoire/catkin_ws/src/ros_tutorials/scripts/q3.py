#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
import math
class ClosedLoopTurtlebot3:
    def __init__(self, target_x, target_y, kp_linear=1.0, kp_angular=4.0, tolerance=0.1):
        rospy.init_node('closed_loop_turtlebot3', anonymous=True)
        # Publishers et Subscribers
        self.vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
        self.odom_sub = rospy.Subscriber('/odom', Odometry, self.update_pose)
        # Paramètres de contrôle
        self.target_x = target_x
        self.target_y = target_y
        self.kp_linear = kp_linear
        self.kp_angular = kp_angular
        self.tolerance = tolerance
        # État actuel du robot
        self.current_x = 0.0
        self.current_y = 0.0
        self.current_yaw = 0.0
        self.new_pose_received = False
        self.rate = rospy.Rate(10)  # 10 Hz
    def update_pose(self, data):
        """Met à jour la position et l'orientation actuelle du robot."""
        self.current_x = data.pose.pose.position.x
        self.current_y = data.pose.pose.position.y
        # Calculer l'orientation actuelle (yaw)
        orientation_q = data.pose.pose.orientation
        siny_cosp = 2 * (orientation_q.w * orientation_q.z + orientation_q.x * orientation_q.y)
        cosy_cosp = 1 - 2 * (orientation_q.y ** 2 + orientation_q.z ** 2)
        self.current_yaw = math.atan2(siny_cosp, cosy_cosp)
        # Indique que de nouvelles données ont été reçues
        self.new_pose_received = True
    def calculate_distance(self):
        """Calcule la distance entre la position actuelle et la cible."""
        return math.sqrt((self.target_x - self.current_x)**2 + (self.target_y - self.current_y)**2)
    def calculate_angle(self):
        """Calcule l'angle vers la cible par rapport à l'orientation actuelle."""
        return math.atan2(self.target_y - self.current_y, self.target_x - self.current_x) - self.current_yaw
    def move_to_goal(self):
        """Déplace le robot vers la cible en utilisant un contrôle P."""
        vel_msg = Twist()
        rospy.loginfo("Démarrage du déplacement vers la cible...")
        while not rospy.is_shutdown():
            if not self.new_pose_received:
                rospy.logwarn("En attente de nouvelles données de pose...")
                self.rate.sleep()
                continue
            # Calcul des erreurs
            distance_error = self.calculate_distance()
            angle_error = self.calculate_angle()
            # Conditions d'arrêt
            if distance_error < self.tolerance:
                rospy.loginfo("Cible atteinte!")
                break
            # Commandes P-control
            vel_msg.linear.x = min(self.kp_linear * distance_error, 0.3)  # Limite de vitesse linéaire
            vel_msg.angular.z = max(min(self.kp_angular * angle_error, 2.0), -2.0)  # Limite de vitesse angulaire
            # Publier les commandes
            self.vel_pub.publish(vel_msg)
            rospy.loginfo(f"Distance Error: {distance_error:.2f} | Linear Velocity: {vel_msg.linear.x:.2f} | Angular Velocity: {vel_msg.angular.z:.2f}")
            self.rate.sleep()
        # Arrêter le robot
        self.stop_robot()
    def stop_robot(self):
        """Arrête le robot."""
        rospy.loginfo("Arrêt du robot.")
        vel_msg = Twist()
        self.vel_pub.publish(vel_msg)
if __name__ == '__main__':
    try:
        # Paramètres de la cible et gains
        target_x = 6.0  # Position cible en x
        target_y = 0.0  # Position cible en y
        kp_linear = 1.0
        kp_angular = 4.0
        # Initialisation et exécution du contrôle
        turtlebot = ClosedLoopTurtlebot3(target_x, target_y, kp_linear, kp_angular)
        rospy.sleep(2)  # Attente pour l'initialisation de la simulation
        turtlebot.move_to_goal()
    except rospy.ROSInterruptException:
        pass
