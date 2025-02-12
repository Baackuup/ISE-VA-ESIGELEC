#!/usr/bin/env python3

import rospy
import tf

def tf_listener():
    rospy.init_node('turtle_tf_listener', anonymous=True)

    listener = tf.TransformListener()
    rate = rospy.Rate(10)  # 10 Hz

    while not rospy.is_shutdown():
        try:
            # Obtenir la transformation entre turtle1 et turtle2
            (trans, rot) = listener.lookupTransform('/turtle1', '/turtle2', rospy.Time(0))

            # Afficher les différences de translation et de rotation
            rospy.loginfo("Translation (x, y, z): %s", trans)
            rospy.loginfo("Rotation (x, y, z, w): %s", rot)

        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException) as e:
            rospy.logwarn("TF Exception: %s", e)

        rate.sleep()

if __name__ == '__main__':
    try:
        tf_listener()
    except rospy.ROSInterruptException:
        pass
