#!/usr/bin/env python3

import rospy
from turtlesim.srv import Spawn, SpawnRequest
from std_srvs.srv import Trigger, TriggerResponse
from geometry_msgs.msg import Twist

def handle_spawn_turtle(req):
    try:
        # Appeler le service '/spawn' pour ajouter turtle2
        rospy.wait_for_service('/spawn')
        spawn_turtle = rospy.ServiceProxy('/spawn', Spawn)

        # Définir la position initiale de turtle2
        x = 5.5
        y = 3.5
        theta = 0.0  # Orientation initiale
        name = "turtle2"

        # Effectuer la requête de création de turtle2
        response = spawn_turtle(x, y, theta, name)
        rospy.loginfo(f"Turtle '{response.name}' spawned at ({x}, {y}).")

        # Commander le mouvement des deux tortues
        move_both_turtles()

        return TriggerResponse(success=True, message=f"Turtle '{response.name}' spawned and moved successfully.")
    except Exception as e:
        rospy.logerr(f"Failed to spawn or move turtles: {e}")
        return TriggerResponse(success=False, message=f"Failed to spawn or move turtles: {e}")

def move_both_turtles():
    # Créer des éditeurs pour les topics /turtle1/cmd_vel et /turtle2/cmd_vel
    pub_turtle1 = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)
    pub_turtle2 = rospy.Publisher('/turtle2/cmd_vel', Twist, queue_size=10)

    # Définir le mouvement en avant
    vel_msg = Twist()
    vel_msg.linear.x = 1.0  # Avancer à 1 m/s
    vel_msg.angular.z = 0.0  # Pas de rotation

    # Temps de mouvement pour couvrir 2 mètres
    move_duration = 2.0  # En secondes (1 m/s * 2 s = 2 m)

    # Début du mouvement
    start_time = rospy.Time.now().to_sec()
    rate = rospy.Rate(10)  # 10 Hz

    while rospy.Time.now().to_sec() - start_time < move_duration:
        pub_turtle1.publish(vel_msg)
        pub_turtle2.publish(vel_msg)
        rate.sleep()

    # Arrêter les deux tortues après 2 mètres
    vel_msg.linear.x = 0.0
    pub_turtle1.publish(vel_msg)
    pub_turtle2.publish(vel_msg)
    rospy.loginfo("Both turtles have stopped after moving 2 meters.")

def spawn_turtle_service():
    # Initialiser le nœud ROS
    rospy.init_node('spawn_turtle_service', anonymous=True)

    # Créer un serveur de service pour '/spawn_turtle'
    service = rospy.Service('/spawn_turtle', Trigger, handle_spawn_turtle)

    rospy.loginfo("Spawn turtle service is ready.")
    rospy.spin()

if __name__ == '__main__':
    try:
        spawn_turtle_service()
    except rospy.ROSInterruptException:
        pass

