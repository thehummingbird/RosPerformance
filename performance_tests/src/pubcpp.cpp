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
  msg.header.frame_id = "/world";
  int count =0;
  ros::Rate loop_rate(500);
  while(ros::ok())
  {
    msg.header.stamp = ros::Time::now();
    msg.data = "hello"+std::to_string(count);
    Obj.cpp_publisher.publish(msg);
    count++;
    loop_rate.sleep();
    //ROS_INFO("Publishing\n");
  }		
  return 0;
	
}
