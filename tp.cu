#include <cuda_runtime.h>
#include <opencv2/opencv.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp>
#include <iostream>
#include <stdio.h>

#include "include/config.hpp"
#include "include/imutil.hpp"
#include "include/eta.hpp"
#include "include/file.hpp"

using namespace std;
using namespace cv;
using namespace cv::cuda;

__global__ void blendAndCompareKernel(uchar* composite, uchar* image, uchar* nextImage, int cols, int rows, int threshold, float alpha) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < cols && y < rows) {
        int idx = y * cols + x;
        int baseIdx = idx * 3;

        uchar p_composite[3];
        uchar p_now[3];
        uchar p_next[3];

        p_composite[0] = composite[baseIdx];
        p_composite[1] = composite[baseIdx + 1];
        p_composite[2] = composite[baseIdx + 2];

        p_now[0] = image[baseIdx];
        p_now[1] = image[baseIdx + 1];
        p_now[2] = image[baseIdx + 2];

        p_next[0] = nextImage[baseIdx];
        p_next[1] = nextImage[baseIdx + 1];
        p_next[2] = nextImage[baseIdx + 2];

        float average_now = (p_now[0] + p_now[1] + p_now[2]) / 3.0f;
        float average_next = (p_next[0] + p_next[1] + p_next[2]) / 3.0f;

        if (average_next - average_now > threshold) {
            composite[baseIdx] = static_cast<uchar>(alpha * p_next[0] + (1.0f - alpha) * p_composite[0]);
            composite[baseIdx + 1] = static_cast<uchar>(alpha * p_next[1] + (1.0f - alpha) * p_composite[1]);
            composite[baseIdx + 2] = static_cast<uchar>(alpha * p_next[2] + (1.0f - alpha) * p_composite[2]);
        }
    }
}

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

        sprintf(image_name, "%s/%d.%s", config.input_folder.c_str(), i, input_att.file_extension.c_str());

        image = imread(image_name);
        writer.write(image);
    }
    writer.release();

    return 0;
}

int afterimage_timelapse(Config config, Input input_att) {
    ETA eta(config.num_of_frames);

    char image_name[100];
    GpuMat image;
    GpuMat compositeimage;

    VideoWriter writer;
    writer.open(
        config.output_file,
        VideoWriter::fourcc('I', 'Y', 'U', 'V'),
        config.fps,
        Size(config.width, config.height),
        true
    );
    if (!writer.isOpened()) return -1;

    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((config.width + threadsPerBlock.x - 1) / threadsPerBlock.x, (config.height + threadsPerBlock.y - 1) / threadsPerBlock.y);

    for (int i = 1; i <= config.num_of_frames; i++) {
        eta.update();
    
        sprintf(image_name, "%s/%d.%s", config.input_folder.c_str(), i, input_att.file_extension.c_str());
        Mat hostImage = imread(image_name);
    
        if (!hostImage.empty()) {
            GpuMat image;
            image.upload(hostImage);
    
            if (i == 1) {
                compositeimage = image.clone();
            } else {
                blendAndCompareKernel<<<numBlocks, threadsPerBlock>>>(compositeimage.data, image.data, compositeimage.data, config.width, config.height, config.threshold, config.alpha);
            }
    
            Mat compositeHost;
            compositeimage.download(compositeHost);
            writer.write(compositeHost);
        }
    }
    writer.release();

    return 0;
}

int main(int argc, char *argv[]) {
    Config config;
    if (argc == 1) config = config_loader("../assets/example.cfg");
    else if (argc == 2) config = config_loader(argv[1]);
    
    Input input_att = get_input_attributes(config.input_folder);
    if (config.num_of_frames == 0) config.num_of_frames = input_att.file_num;
    
    ImageSize image_size = get_image_size(config);
    config.width = image_size.width;
    config.height = image_size.height;

    config_printer(config);
    
    if (config.mode == 0) normal_timelapse(config, input_att);
    else if (config.mode == 1) afterimage_timelapse(config, input_att);

    return 0;
}
