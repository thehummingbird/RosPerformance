#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"
#include "performance_tests/LoopRate.h"

class SubCpp
{
public:
  SubCpp();
  ros::Subscriber cpp_subscriber;
  ros::ServiceClient updateLoopRate;
  void msg_callback(const performance_tests::SuperAwesome msg);
  void calculate_frequency();
  void update_rate();

private:
  ros::NodeHandle n;
  double meanTime;
  double freq;
  double currTime;
  double prevTime;
  int count = 0;
  int currRateIndex;
  int rates[17] = {10,50,100,200,500,1000,1500,2000,2500,4000,5000,8000,10000,12000,15000,20000,25000};

};

SubCpp::SubCpp()
{
  cpp_subscriber = n.subscribe("/publishMsg",100,&SubCpp::msg_callback,this);
  updateLoopRate = n.serviceClient<performance_tests::LoopRate>("loop_rate");
  currRateIndex = 0;
  meanTime=-1;
  freq=0;
  currTime=-1;
  prevTime=-1;
  count = 0;

}

void SubCpp::calculate_frequency()
{
  //method to calculate the average loop rate after every callback

  currTime =ros::Time::now().toSec();
  if(prevTime != -1)
  {
    double timeDiff = currTime - prevTime;
    if(meanTime != -1)
    {
      //running mean
      meanTime = meanTime + ((timeDiff-meanTime)/count);
    }
    else 
      meanTime = timeDiff;
    freq = (1/meanTime); //average loop rate
    count++;
  }

  prevTime = currTime;
  if(count==(rates[currRateIndex]*9))
  {
    //log data when runtime = 9 seconds (out of 10)
    ROS_INFO("Current loop rate = %d; Actual loop rate = %f\n", rates[currRateIndex],freq);
    if(currRateIndex == 16)
    { 
      //shutdown subscriber when all the rates are tested for
      ROS_INFO("End of Test\n");
      cpp_subscriber.shutdown();
    }
  }
  
}

void SubCpp::update_rate()
{
  //method to update current loop rate if the previous loop ran for 10 seconds

  if(count == rates[currRateIndex]*10)
  {
    currRateIndex++;
    meanTime=-1;
    freq=0;
    currTime=-1;
    prevTime=-1;
    count = 0;
    performance_tests::LoopRate srv;
    
    //update loop rate
    srv.request.rate = -1;
    if(!updateLoopRate.call(srv))
      ROS_ERROR("Failed to update loop rate");
    ros::Duration(1).sleep();
    srv.request.rate = rates[currRateIndex];
    if(!updateLoopRate.call(srv))
      ROS_ERROR("Failed to update loop rate");
    ROS_INFO("Updated loop rate to %d\n",rates[currRateIndex]);
    ros::Duration(1).sleep();
  }

}

void SubCpp::msg_callback(const performance_tests::SuperAwesome msg)
{
  //callback method

  calculate_frequency();
  update_rate();

}

int main(int argc,char** argv)
{
  ros::init(argc,argv,"sub_cpp");
  SubCpp Obj;
 
  ros::spin();		
  return 0;
	
}
