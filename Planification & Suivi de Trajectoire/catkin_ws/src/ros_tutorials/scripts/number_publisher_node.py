#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int64

def number_publisher():
    # Initialiser le nœud
    rospy.init_node('number_publisher_node', anonymous=True)

    # Créer un éditeur pour publier sur le topic '/number'
    pub = rospy.Publisher('/number', Int64, queue_size=10)

    # Définir le taux de publication (1 Hz)
    rate = rospy.Rate(1)

    # Nombre constant à publier
    number = Int64()
    number.data = 10

    while not rospy.is_shutdown():
        # Publier le nombre constant
        pub.publish(number)
        rospy.loginfo(f"Published: {number.data}")
        rate.sleep()

if __name__ == '__main__':
    try:
        number_publisher()
    except rospy.ROSInterruptException:
        pass

