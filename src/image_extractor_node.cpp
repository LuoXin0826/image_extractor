#include <ros/ros.h>
#include <iostream>
#include <chrono>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>

class Extractor{
public:
	Extractor():
	nh_("~"),
	image_counter_(0),
	extraction_counter_(0),
	extraction_period_(0.3)
	{
		ros::Subscriber sub = nh_.subscribe("/wamv/sensors/cameras/front_left_camera/image_raw/compressed", 1000, &Extractor::extractorCallback, this);
		ros::spin();
	}

private:

	void extractorCallback(const sensor_msgs::CompressedImageConstPtr& image){
		cv_bridge::CvImagePtr cvImg = cv_bridge::toCvCopy(image, "bgr8");
  		cv::Mat myOpenCVImg = cvImg->image;
  		extraction_counter_++;
  		if(extraction_counter_%(int)(extraction_period_*10) == 0){
  			image_counter_++;
  			// // rotate the image by 90 degree clockwise (ignore this when extracting simulation images)
  			// cv::Mat temp,dst;
  			// transpose(myOpenCVImg, temp);
  			// flip(temp, dst, 1);
	    	// imwrite( "./src/image_extractor/extracted_images/image" + std::to_string(image_counter_) + ".png", dst);
        imwrite( "./src/image_extractor/extracted_images/image" + std::to_string(image_counter_) + ".png", myOpenCVImg);
  		}
	}

    // handler
    ros::NodeHandle nh_;
 	//counter
    int image_counter_;
    int extraction_counter_;
    float extraction_period_;

};


int main(int argc, char* argv[]) 
{
  ROS_INFO_STREAM("====================Image Extractor Node Started=====================");
  ros::init(argc, argv, "image_extractor_node");

  Extractor extractor;

  return 0;
}