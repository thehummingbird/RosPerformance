#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"

class PubCpp
{
public:
  PubCpp();
  ros::Publisher cpp_publisher;

private:
  ros::NodeHandle n;

};

PubCpp::PubCpp()
{
  cpp_publisher = n.advertise<performance_tests::SuperAwesome>("/publishMsg",100);

}

int main(int argc,char** argv)
{
  ros::init(argc,argv,"pub_cpp");
  PubCpp Obj;
  performance_tests::SuperAwesome msg;

  double rate;
  if (!(ros::param::get("/pub_cpp/cpp_pub_rate",rate)))
  {
	ROS_ERROR("No 'cpp_pub_rate'");
  }
  ros::Rate loop_rate(rate);

  while(ros::ok())
  {
    msg.header.stamp = ros::Time::now();
    msg.data = "Publisher";
    Obj.cpp_publisher.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();

  }	
	
  return 0;
	
}
