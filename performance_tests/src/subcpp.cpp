#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"


class SubCpp
{
public:
  SubCpp();
  ros::Subscriber cpp_subscriber;
  void msg_callback(const performance_tests::SuperAwesome msg);

private:
  ros::NodeHandle n;

};

SubCpp::SubCpp()
{
  cpp_subscriber = n.subscribe("/publishMsg",100,&SubCpp::msg_callback,this);

}

void SubCpp::msg_callback(const performance_tests::SuperAwesome msg)
{
  ROS_INFO("%s",msg.data.c_str());

}
int main(int argc,char** argv)
{
  ros::init(argc,argv,"sub_cpp");
  SubCpp Obj;
 

  ros::spin();		
  return 0;
	
}
