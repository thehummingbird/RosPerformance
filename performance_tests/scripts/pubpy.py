#!/usr/bin/env python
import rospy
from performance_tests.msg import SuperAwesome

def publisher():
    PubPy = rospy.Publisher('/publishMsg', SuperAwesome,queue_size=10)
    rospy.init_node('pub_py', anonymous=True)
    r = rospy.Rate(10) #10hz
    msg = SuperAwesome()
    msg.data = "PyHello"

    while not rospy.is_shutdown():
        rospy.loginfo(msg)
        msg.header.stamp = rospy.Time.now()
        PubPy.publish(msg)
        r.sleep()

if __name__ == '__main__':
    try:
        publisher()
    except rospy.ROSInterruptException: pass
