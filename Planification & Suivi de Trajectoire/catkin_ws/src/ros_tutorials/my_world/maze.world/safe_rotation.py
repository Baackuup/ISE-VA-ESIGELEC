#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import LaserScan
import math
import time

# Distance de sécurité minimale (en mètres)
SAFE_DISTANCE = 0.5
# Tolérance pour considérer que l'angle cible est atteint
ANGLE_TOLERANCE = 0.05

# Variable globale pour stocker la distance minimale détectée par le scanner laser
min_distance = float('inf')

def scan_callback(scan_data):
    """
    Callback pour traiter les données du scanner laser.
    Met à jour la distance minimale détectée.
    """
    global min_distance
    min_distance = min(scan_data.ranges)

def rotate_robot(target_angle_deg):
    """
    Fonction pour faire tourner le TurtleBot3 d'un angle spécifique en degrés.
    """
    global min_distance

    # Convertir l'angle cible en radians
    target_angle_rad = math.radians(target_angle_deg)

    # Initialiser le nœud ROS
    rospy.init_node('safe_rotation', anonymous=True)

    # Création du Publisher pour commander la vitesse
    velocity_publisher = rospy.Publisher('/cmd_vel', Twist, queue_size=10)

    # S'abonner au topic /scan pour recevoir les données du scanner laser
    rospy.Subscriber('/scan', LaserScan, scan_callback)

    # Définir un Twist pour la rotation
    vel_msg = Twist()
    vel_msg.linear.x = 0.0  # Pas de mouvement linéaire
    vel_msg.angular.z = 0.5  # Vitesse angulaire (positive pour antihoraire)

    # Temps de début pour calculer la rotation
    start_time = time.time()
    current_angle = 0.0

    rate = rospy.Rate(10)  # 10 Hz

    rospy.loginfo(f"Début de la rotation de {target_angle_deg}°")

    while not rospy.is_shutdown():
        # Vérifier la distance minimale par rapport aux obstacles
        if min_distance < SAFE_DISTANCE:
            rospy.logwarn(f"Obstacle détecté à {min_distance:.2f} m. Arrêt de la rotation.")
            break

        # Calculer l'angle tourné en utilisant le temps écoulé
        elapsed_time = time.time() - start_time
        current_angle = elapsed_time * abs(vel_msg.angular.z)

        rospy.loginfo(f"Angle actuel : {math.degrees(current_angle):.2f}°")

        # Vérifier si l'angle cible est atteint
        if abs(current_angle - target_angle_rad) < ANGLE_TOLERANCE:
            rospy.loginfo(f"Rotation de {target_angle_deg}° complétée.")
            break

        # Publier le message de vitesse
        velocity_publisher.publish(vel_msg)
        rate.sleep()

    # Arrêter le robot après la rotation
    vel_msg.angular.z = 0.0
    velocity_publisher.publish(vel_msg)
    rospy.loginfo("Rotation terminée, le robot est à l'arrêt.")

if __name__ == '__main__':
    try:
        # Exemple : Faire tourner le robot de 90° dans le sens antihoraire
        rotate_robot(90)
    except rospy.ROSInterruptException:
        pass

