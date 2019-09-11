#!/usr/bin/env python
import rospy, time
from performance_tests.msg import SuperAwesome
from performance_tests.srv import *

loopRate = 10
changeLoopRate = 0
rate = None

def handle_looprate_request(request):
    global loopRate
    global changeLoopRate
    loopRate = request.rate
    changeLoopRate = 1
    return LoopRateResponse()
     

def publisher():
    rospy.init_node('pub_py')
    PubPy = rospy.Publisher('/publishMsg', SuperAwesome,queue_size=100)
    s = rospy.Service("loop_rate", LoopRate, handle_looprate_request)
    msg = SuperAwesome()
    
    global rate
    global changeLoopRate
    global loopRate
    rate=rospy.Rate(loopRate)
    while not rospy.is_shutdown():
        if(changeLoopRate == 1):
            if(loopRate == -1):
                time.sleep(0.05)
		continue
            rate = rospy.Rate(loopRate)
            changeLoopRate = 0
            rospy.sleep(1)
        msg.data = "Publishing"
        PubPy.publish(msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        publisher()
    except rospy.ROSInterruptException: pass
