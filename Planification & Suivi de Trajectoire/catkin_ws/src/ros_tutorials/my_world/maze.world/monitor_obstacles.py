#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import LaserScan

# Seuil de distance minimale en mètres
MIN_DISTANCE_THRESHOLD = 0.2

def scan_callback(scan_data):
    """
    Callback pour traiter les données du scanner laser.
    """
    # Trouver la distance minimale dans le tableau de distances
    min_distance = min(scan_data.ranges)
    rospy.loginfo(f"Minimal distance : {min_distance:.2f} m")

    # Vérifier si la distance est inférieure au seuil
    if min_distance < MIN_DISTANCE_THRESHOLD:
        rospy.logwarn("Attention! Maintain a safe distance from obstacles.")

def main():
    """
    Fonction principale pour initialiser le nœud ROS.
    """
    # Initialiser le nœud
    rospy.init_node('obstacle_monitor', anonymous=True)

    # S'abonner au topic /scan
    rospy.Subscriber('/scan', LaserScan, scan_callback)

    rospy.loginfo("node activated")
    rospy.spin()  # Maintenir le nœud actif

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass

