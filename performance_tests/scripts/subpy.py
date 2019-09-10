#!/usr/bin/env python
import rospy
from performance_tests.msg import SuperAwesome

def callback(message):
    #rospy.loginfo("message is %s with timestamp %f" % (message.data,message.header.stamp))
    print('Message is '+message.data+' with timestamp '+str(message.header.stamp)+'\n');

def subscriber():
    rospy.init_node('sub_py', anonymous=True)
    rospy.Subscriber("/publishMsg", SuperAwesome, callback)

    rospy.spin()

if __name__ == '__main__':
    subscriber()
