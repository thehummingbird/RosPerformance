#!/usr/bin/env python
import rospy
from performance_tests.msg import SuperAwesome

def callback(message):
    print message.data;

def subscriber():
    rospy.init_node('sub_py')
    rospy.Subscriber("/publishMsg", SuperAwesome, callback,queue_size=100)

    rospy.spin()

if __name__ == '__main__':
    subscriber()
