#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"
#include "performance_tests/LoopRate.h"

class PubCpp
{
public:
  PubCpp();
  ros::Publisher cpp_publisher;
  int loopRate;
  bool changeLoopRate;
  bool handle_looprate_request(performance_tests::LoopRate::Request& req, performance_tests::LoopRate::Response& res);

private:
  ros::NodeHandle n;
  ros::ServiceServer service;

};

PubCpp::PubCpp()
{
  cpp_publisher = n.advertise<performance_tests::SuperAwesome>("/publishMsg",100);
  service = n.advertiseService("loop_rate",&PubCpp::handle_looprate_request,this);
  loopRate = 10;
  changeLoopRate = false;

}

bool PubCpp::handle_looprate_request(performance_tests::LoopRate::Request& req, performance_tests::LoopRate::Response& res)
{
  //handler to service loop rate update request
  loopRate = req.rate;
  changeLoopRate = true;
  return true;
  
}

int main(int argc,char** argv)
{
  ros::init(argc,argv,"pub_cpp");
  PubCpp Obj;
  performance_tests::SuperAwesome msg;

  ros::Rate loop_rate(Obj.loopRate);

  while(ros::ok())
  {
    if(Obj.changeLoopRate)
    {
      if(Obj.loopRate == -1)
      {
	ros::spinOnce();
	ros::Duration(0.01).sleep();
      }
      
      //update loop rate
      loop_rate = ros::Rate(Obj.loopRate);
      Obj.changeLoopRate = false;
      ros::Duration(1).sleep();
    }
    msg.data = "Publisher";
    Obj.cpp_publisher.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();

  }	
	
  return 0;
	
}
