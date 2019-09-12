# C++ Vs Python in ROS

The package performance_tests compares C++ and Python speeds in ROS by looking at the following 4 combinations:
1. Cpp Publisher and Python Subscriber
2. Cpp Publisher and Cpp Subscriber
3. Python Publisher and Cpp Subscriber
4. Python Publisher and Python Subscriber

There are 4 launch files in the package for them:
1. PubCppSubPy.launch
2. PubCppSubCpp.launch
3. PubPySubCpp.launch
4. PubPySubPy.launch

Each of these launch pub-sub communication at the following expected rates-
[10,50,100,200,500,1000,1500,2000,2500,4000,5000,8000,10000,12000,15000,20000,25000]

To capture and log data, each rate is used for 10 seconds and an average loop rate (appromixate actual loop rate) is calculated and logged in /.ros/log/latest/rosout.log

Observed rate at which actual rate deviates from the expected rate:

1. Cpp Publisher and Python Subscriber: 25000 Hz
2. Cpp Publisher and Cpp Subscriber: 12000 Hz
3. Python Publisher and Cpp Subscriber: 4000 Hz
4. Python Publisher and Python Subscriber: 1000 Hz

Logs with the same information can be found in the package as Out_PubCpp_SubPy.log, Out_PubCpp_SubCpp.log, Out_PubPy_SubCpp.log, Out_PubPy_SubPy.log respectively

Cheers!
