#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

struct ImageSize {
    int width;
    int height;
};

ImageSize get_image_size(string filename) {
    ImageSize image_size;
    cv::Mat image = cv::Mat::zeros(0, 0, CV_8UC3);

    image = cv::imread(filename);
    
    image_size.width = image.cols;
    image_size.height = image.rows;
    
    return image_size;
}
