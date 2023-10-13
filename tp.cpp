#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

#include "include/config.hpp"
#include "include/imutil.hpp"
#include "include/eta.hpp"
#include "include/file.hpp"

using namespace std;
using namespace cv;

int normal_timelapse(Config config, Input input_att) {
    ETA eta(config.num_of_frames);

    char image_name[100];    
    Mat image = Mat::zeros(config.height, config.width, CV_8UC3);

    // output movie file, non-compresse avi format
    VideoWriter writer;
    writer.open(
        config.output_file, 
        VideoWriter::fourcc('I', 'Y', 'U', 'V'), 
        config.fps, 
        Size(config.width, config.height), 
        true
    );
    if (!writer.isOpened()) return -1;
    for (int i = 1; i <= config.num_of_frames; i++) {
        eta.update();

        sprintf(image_name, "%s/%d.%s", config.output_file.c_str(), i, input_att.file_extension.c_str());

        image = imread(image_name);
        writer.write(image);
    }
    writer.release();

    return 0;
}

int afterimage_timelapse(Config config, Input input_att) {
    ETA eta(config.num_of_frames);

    // base image
    char image_name[100];
    Mat image = Mat::zeros(config.height, config.width, CV_8UC3);
    // composite image
    Mat compositeimage = Mat::zeros(config.height, config.width, CV_8UC3);

    // output movie file, non-compressed avi format
    VideoWriter writer;
    writer.open(
        config.output_file, 
        VideoWriter::fourcc('I', 'Y', 'U', 'V'), 
        config.fps, 
        Size(config.width, config.height), 
        true
    );
    if (!writer.isOpened()) return -1;

    for (int i = 1; i <= config.num_of_frames; i++) {
        eta.update();

        // comparative brightness synthesis images
        sprintf(image_name, "%s/%d.%s", config.input_folder.c_str(), i, input_att.file_extension.c_str());
        image = imread(image_name);
        
        if (i == 1) {
            compositeimage = image.clone();
        } else {
            compositeimage.clone().convertTo(compositeimage, -1, 1, -config.alpha);
            for (int y = 0; y < image.rows; y++) {
                for (int x = 0; x < image.cols; x++) {
                    cv::Vec3b &p_composite = image.at<cv::Vec3b>(y, x);
                    cv::Vec3b &p_now = image.at<cv::Vec3b>(y, x);
                    cv::Vec3b &p_next = compositeimage.at<cv::Vec3b>(y, x);
                    int average_now = (p_now[0] + p_now[1] + p_now[2]) / 3;
                    int average_next = (p_next[0] + p_next[1] + p_next[2]) / 3;
                    if (average_next - average_now > config.threshold) {
                        p_composite[0] = p_next[0];
                        p_composite[1] = p_next[1];
                        p_composite[2] = p_next[2];
                    }
                }
            }
            compositeimage = image.clone();
        }
        writer.write(image);
    }
    writer.release();

    return 0;
} 

int main() {
    Config config = config_loader("../assets/example.cfg");
    
    Input input_att = get_input_attributes(config.input_folder);
    if (config.num_of_frames == 0) config.num_of_frames = input_att.file_num;
    
    ImageSize image_size = get_image_size(config);
    config.width = image_size.width;
    config.height = image_size.height;

    config_printer(config);
    
    if (config.mode == 0) {
        normal_timelapse(config, input_att);
    } else if (config.mode == 1) {
        afterimage_timelapse(config, input_att);
    }

    return 0;
}
