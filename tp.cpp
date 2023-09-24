#include <opencv2/opencv.hpp>
#include "progress.hpp"
#include "config.hpp"

#include <iostream>
#include <stdio.h>

#define THRESHOLD 20

using namespace std;
using namespace cv;

int normal_timelapse(Config config) {
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

        // progress_bar(i, config.num_of_frames);

        sprintf(image_name, "../data/from2/%d.jpg", i);

        image = imread(image_name);
        writer.write(image);
    }
    writer.release();

    return 0;
}

int afterimage_timelapse(Config config) {
    int count = 0;
    int j = 0;
    int idx = 0;
    int alpha_idx = 0;

    // base image
    char image_name[100];
    Mat image = Mat::zeros(config.height, config.width, CV_8UC3);
    // afterimages
    Mat afterimages[config.level];
    for (int i = 0; i < config.level; i++) {
        afterimages[i] = Mat::zeros(config.height, config.width, CV_8UC3);
    }
    // afterimage
    Mat afterimage = Mat::zeros(config.height, config.width, CV_8UC3);
    Mat compositeimage = Mat::zeros(config.height, config.width, CV_8UC3);

    // brightness coefficient
    // -50 - 0 
    int alpha[config.level];
    for (int i = 0; i < config.level; i++) {
        alpha[i] = -50 + 50 * i / (config.level - 1);
    }

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
        progress_bar(i, config.num_of_frames);

        // comparative brightness synthesis images
        count = min(i, config.level);
        j = (i - 1) % config.level;
        idx = (j - 1) % config.level; if (idx < 0) idx += config.level;

        sprintf(image_name, "../data/from2/%d.jpg", i);
        image = imread(image_name);
        afterimages[j] = image.clone();

        while(count--) {
            afterimages[idx].clone().convertTo(afterimage, -1, 1, alpha[count]);
            
            for (int y = 0; y < image.rows; y++) {
                for (int x = 0; x < image.cols; x++) {
                    cv::Vec3b &p_composite = image.at<cv::Vec3b>(y, x);
                    cv::Vec3b &p_now = image.at<cv::Vec3b>(y, x);
                    cv::Vec3b &p_next = afterimage.at<cv::Vec3b>(y, x);
                    int average_now = (p_now[0] + p_now[1] + p_now[2]) / 3;
                    int average_next = (p_next[0] + p_next[1] + p_next[2]) / 3;
                    if (average_next - average_now > THRESHOLD) {
                        p_composite[0] = p_next[0];
                        p_composite[1] = p_next[1];
                        p_composite[2] = p_next[2];
                    }
                }
            }

            idx = idx - 1 % config.level; if (idx < 0) idx += config.level;
        }
        writer.write(image);
    }
    writer.release();

    return 0;
} 

int main() {
    Config config = config_loader("../assets/example.cfg");

    config_printer(config);

    if (config.mode == 0) {
        normal_timelapse(config);
    } else if (config.mode == 1) {
        afterimage_timelapse(config);
    }

    return 0;
}
