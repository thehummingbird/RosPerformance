#!/usr/bin/env python
import rospy
from performance_tests.msg import SuperAwesome

def publisher():
    PubPy = rospy.Publisher('/publishMsg', SuperAwesome,queue_size=100)
    rospy.init_node('pub_py')
    msg = SuperAwesome()
    
    rate = rospy.Rate(rospy.get_param("/pub_py/py_pub_rate"))
    while not rospy.is_shutdown():
        #rospy.loginfo(msg)
        msg.header.stamp = rospy.Time.now()
        msg.data = "Publishing"
        PubPy.publish(msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        publisher()
    except rospy.ROSInterruptException: pass
