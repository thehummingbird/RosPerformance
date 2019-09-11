#!/usr/bin/env python
import rospy, time
from performance_tests.msg import SuperAwesome
from performance_tests.srv import *

meanTime = -1.000
freq = 0.000
currTime = -1.000
prevTime = -1.000
count = 0;
rates = [10,50,100,200,500,1000,1500,2000,2500,4000,5000,8000,10000,12000,15000,20000,25000]
currRateIndex = 0
py_subscriber = None
def calculate_frequency():
    global meanTime
    global freq
    global currTime
    global prevTime
    global count
    global currRateIndex
    currTime = rospy.get_time()
    if(prevTime!=-1):
        timeDiff = currTime - prevTime
        if(meanTime!=-1):
            meanTime = meanTime + ((timeDiff-meanTime)/count);
        else:
            meanTime = timeDiff
        freq= 1/meanTime
        count+=1
    prevTime=currTime
    if(count==(rates[currRateIndex]*9)):
        rospy.loginfo("Current loop rate = %d; Actual loop rate = %f\n" % (rates[currRateIndex],freq))
        if(currRateIndex == 16):
            rospy.loginfo("End of Test\n")
            py_subscriber.unregister()
            
def update_rate():
    global meanTime
    global freq
    global currTime
    global prevTime
    global count
    global currRateIndex
    if(count == rates[currRateIndex]*10):
        currRateIndex+=1
        meanTime=-1
        freq=0
        currTime=-1
        prevTime=-1
        count = 0
        rospy.wait_for_service("loop_rate")
        svc = rospy.ServiceProxy("loop_rate", LoopRate)
        svc(-1)
        time.sleep(1)
        svc(rates[currRateIndex])
        time.sleep(1)
        rospy.loginfo("Updated loop rate to %d\n" % rates[currRateIndex])

def callback(message):
    calculate_frequency()
    update_rate()

def subscriber():
    global py_subscriber
    rospy.init_node('sub_py')
    py_subscriber = rospy.Subscriber("/publishMsg", SuperAwesome, callback,queue_size=100)

    rospy.spin()

if __name__ == '__main__':
    subscriber()
