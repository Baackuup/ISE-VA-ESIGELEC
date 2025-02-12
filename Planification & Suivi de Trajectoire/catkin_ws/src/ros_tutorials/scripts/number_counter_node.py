#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int64

# Initialisation du compteur
message_count = 0

# Fonction de rappel pour le Subscriber
def number_callback(msg):
    global message_count
    message_count += 1
    rospy.loginfo(f"Received number: {msg.data}, Count: {message_count}")

def number_counter():
    global message_count

    # Initialiser le nœud
    rospy.init_node('number_counter_node', anonymous=True)

    # Créer un abonné pour le topic '/number'
    rospy.Subscriber('/number', Int64, number_callback)

    # Créer un éditeur pour publier sur le topic '/number_count'
    pub = rospy.Publisher('/number_count', Int64, queue_size=10)

    # Définir le taux de publication (1 Hz)
    rate = rospy.Rate(1)

    while not rospy.is_shutdown():
        # Publier le compteur
        count_msg = Int64()
        count_msg.data = message_count
        pub.publish(count_msg)
        rospy.loginfo(f"Published count: {count_msg.data}")
        rate.sleep()

if __name__ == '__main__':
    try:
        number_counter()
    except rospy.ROSInterruptException:
        pass

