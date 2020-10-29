# image_extractor
This repo contains ros package for extracting images from rosbags for collecting training dataset.

## To Run the package
In catkin_ws/src
```
git clone https://github.com/LuoXin0826/image_extractor.git
cd image_extractor
mkdir extracted_images
cd ../..
```
Modify the image topic name you want to subscribe.
```
catkin_make
source devel/setup.bash
rosrun image_extractor image_extractor_node
```
The extracted images would be stored in 'extracted_images' folder.
