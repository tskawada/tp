#include <opencv2/opencv.hpp>

struct ImageSize {
    int width;
    int height;
};

ImageSize get_image_size(Config config) {
    ImageSize image_size;
    cv::Mat image = cv::Mat::zeros(config.height, config.width, CV_8UC3);

    char image_name[100];
    sprintf(image_name, "../data/from2/%d.jpg", 1);
    
    image = cv::imread(image_name);
    
    image_size.width = image.cols;
    image_size.height = image.rows;
    
    return image_size;
}