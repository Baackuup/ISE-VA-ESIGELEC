#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist

# PID
Kp = 0.045  # Réduit pour éviter des réactions excessives
Ki = 0.0005  # Faible pour minimiser l'accumulation
Kd = 0.04  # Augmenté pour améliorer les corrections fines

desired_distance_from_wall = 0.65  # Distance cible ajustée à 0.55 m
error_sum = 0.0
last_error = 0.0
is_rotating = False

linear_speed = 0.2  # Vitesse linéaire maintenue
max_angular_speed = 0.5  # Vitesse angulaire maximale augmentée

def calculate_pid(setpoint, measured_value):
    global error_sum, last_error
    error = measured_value - setpoint
    error_sum += error
    derivative = error - last_error
    control_signal = (Kp * error) + (Ki * error_sum) + (Kd * derivative)
    last_error = error
    return control_signal

def detect_wall_ahead(scan_data):
    front_distances = scan_data.ranges[0:30] + scan_data.ranges[330:360]
    return any(d < 0.6 for d in front_distances if d > 0.1)  # Détecte un mur devant si < 0.6 m

def is_wall_on_left(scan_data):
    left_distances = scan_data.ranges[30:90]
    return any(d < 0.6 for d in left_distances if d > 0.1)

def wall_following_callback(scan_data):
    global is_rotating, linear_speed
    left_sector = scan_data.ranges[30:90]
    valid_distances = [d for d in left_sector if d > 0.1 and d < scan_data.range_max]

    rospy.loginfo(f"Distances devant : {scan_data.ranges[0:30] + scan_data.ranges[330:360]}")
    rospy.loginfo(f"Distances gauche : {left_sector}")

    # Mode rotation
    if detect_wall_ahead(scan_data):
        rospy.loginfo("Obstacle devant, rotation en cours...")
        is_rotating = True

    if is_rotating:
        vel_msg = Twist()
        vel_msg.linear.x = 0.0
        vel_msg.angular.z = -max_angular_speed  # Rotation rapide à droite
        velocity_publisher.publish(vel_msg)
        
        if is_wall_on_left(scan_data):
            rospy.loginfo("Mur détecté à gauche, fin de rotation")
            is_rotating = False
        return

    # Suivi de mur (comportement normal)
    if valid_distances:
        distance_to_wall = min(valid_distances)
        rospy.loginfo(f"Distance au mur : {distance_to_wall}")
    else:
        rospy.logwarn("Pas de mur détecté à gauche, maintien de la distance cible")
        distance_to_wall = desired_distance_from_wall

    angular_z = calculate_pid(desired_distance_from_wall, distance_to_wall)
    angular_z = max(min(angular_z, max_angular_speed), -max_angular_speed)  # Limite augmentée pour ajustements rapides
    vel_msg = Twist()
    vel_msg.linear.x = linear_speed
    vel_msg.angular.z = angular_z
    velocity_publisher.publish(vel_msg)

if __name__ == "__main__":
    try:
        rospy.init_node('wall_following_node', anonymous=True)
        velocity_publisher = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
        rospy.Subscriber('/scan', LaserScan, wall_following_callback)
        rospy.loginfo("Node de suivi de mur initialisé")
        rospy.spin()
    except rospy.ROSInterruptException:
        rospy.loginfo("Node arrêté")

