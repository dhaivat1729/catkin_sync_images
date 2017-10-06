#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace sensor_msgs;
using namespace message_filters;

int c = 1;

string save_left_image = "/media/dhaivat1729/e4187b00-2f8d-4c09-b475-5966c6563009/Rockwell_collins_fast_stereo/catkin_sync_images/src/Sync_messages/left_images/";
string save_right_image = "/media/dhaivat1729/e4187b00-2f8d-4c09-b475-5966c6563009/Rockwell_collins_fast_stereo/catkin_sync_images/src/Sync_messages/right_images/";

void callback(const ImageConstPtr& image_left, const ImageConstPtr& image_right)
{
  cv_bridge::CvImagePtr cv_ptr_left;
  cv_bridge::CvImagePtr cv_ptr_right;
  cv_ptr_left = cv_bridge::toCvCopy(image_left, sensor_msgs::image_encodings::BGR8);
  cv_ptr_right = cv_bridge::toCvCopy(image_right, sensor_msgs::image_encodings::BGR8);
  //sprintf(save_left_image, "/media/dhaivat1729/e4187b00-2f8d-4c09-b475-5966c6563009/Rockwell_collins_fast_stereo/catkin_ws_tracker/src/Sync_messages/left_images/%4d.jpg", c);
  //sprintf(stringa, "Number of fingers making up a hand are %f", fingers);
  stringstream out;                 
  string image_number;              
  out << c;
  image_number = out.str();
  string save_left_image = "/media/dhaivat1729/e4187b00-2f8d-4c09-b475-5966c6563009/Rockwell_collins_fast_stereo/catkin_sync_images/src/Sync_messages/left_images/";
  string save_right_image = "/media/dhaivat1729/e4187b00-2f8d-4c09-b475-5966c6563009/Rockwell_collins_fast_stereo/catkin_sync_images/src/Sync_messages/right_images/";
  save_left_image = save_left_image + "left_" + image_number + ".jpg";
  save_right_image = save_right_image + "right_" + image_number + ".jpg";
  cout << "Before saving: " << c << endl;
  imwrite(save_left_image, cv_ptr_left->image);
  imwrite(save_right_image, cv_ptr_right->image);
  c++;
  cout << "After saving: " << c << endl;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "vision_node");

  ros::NodeHandle nh;

  message_filters::Subscriber<Image> image_left_sub(nh, "/left_rgb/image", 1);
  message_filters::Subscriber<Image> image_right_sub(nh, "/right_rgb/image", 1);
  TimeSynchronizer<Image, Image> sync(image_left_sub, image_right_sub, 10);
  sync.registerCallback(boost::bind(&callback, _1, _2));
  ros::spin();
  return 0;
}
