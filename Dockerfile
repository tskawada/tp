FROM nvidia/cuda:11.8.0-runtime-ubuntu22.04

ARG DEBIAN_FRONTEND=noninteractive
ARG OPENCV_VERSION=4.5.3

RUN apt-get update && apt-get upgrade -y &&\
    apt-get install -y \
	python3-pip \
        build-essential \
        cmake \
        git \
        wget \
        unzip \
        yasm \
        pkg-config \
        libswscale-dev \
        libtbb2 \
        libtbb-dev \
        libjpeg-dev \
        libpng-dev \
        libtiff-dev \
        libavformat-dev \
        libpq-dev \
        libxine2-dev \
        libglew-dev \
        libtiff5-dev \
        zlib1g-dev \
        libjpeg-dev \
        libavcodec-dev \
        libavformat-dev \
        libavutil-dev \
        libpostproc-dev \
        libswscale-dev \
        libeigen3-dev \
        libtbb-dev \
        libgtk2.0-dev \
        pkg-config \
    && rm -rf /var/lib/apt/lists/*

RUN cd /opt/ &&\
    wget https://github.com/opencv/opencv/archive/$OPENCV_VERSION.zip &&\
    unzip $OPENCV_VERSION.zip &&\
    rm $OPENCV_VERSION.zip &&\
    wget https://github.com/opencv/opencv_contrib/archive/$OPENCV_VERSION.zip &&\
    unzip ${OPENCV_VERSION}.zip &&\
    rm ${OPENCV_VERSION}.zip &&\
    mkdir /opt/opencv-${OPENCV_VERSION}/build && cd /opt/opencv-${OPENCV_VERSION}/build &&\
    cmake \
        -DOPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib-${OPENCV_VERSION}/modules \
        -DWITH_CUDA=ON \
        -DCUDA_ARCH_BIN=7.5,8.0,8.6 \
        -DCMAKE_BUILD_TYPE=RELEASE \
        -DCMAKE_INSTALL_PREFIX=/usr/local \
        .. &&\
    make -j"$(nproc)" && \
    make install && \
    ldconfig &&\
    rm -rf /opt/opencv-${OPENCV_VERSION} && rm -rf /opt/opencv_contrib-${OPENCV_VERSION}

WORKDIR /workspace

COPY . /workspace/

RUN nvcc -o tp tp.cu \
    -I/usr/local/include/opencv4 \
    -lopencv_alphamat \
    -lopencv_aruco \
    -lopencv_barcode \
    -lopencv_bgsegm \
    -lopencv_bioinspired \ 
    -lopencv_calib3d \
    -lopencv_ccalib \
    -lopencv_core \
    -lopencv_cudaarithm \
    -lopencv_cudabgsegm \
    -lopencv_cudacodec \
    -lopencv_cudafeatures2d \
    -lopencv_cudafilters \
    -lopencv_cudaimgproc \
    -lopencv_cudalegacy \
    -lopencv_cudaobjdetect \
    -lopencv_cudaoptflow \
    -lopencv_cudastereo \
    -lopencv_cudawarping \
    -lopencv_cudev \
    -lopencv_datasets \
    -lopencv_dnn \
    -lopencv_dnn_objdetect\ 
    -lopencv_dnn_superres \
    -lopencv_dpm \
    -lopencv_face \
    -lopencv_features2d \
    -lopencv_flann \
    -lopencv_freetype \
    -lopencv_fuzzy \
    -lopencv_gapi \
    -lopencv_hfs \
    -lopencv_highgui \
    -lopencv_img_hash \
    -lopencv_imgcodecs \
    -lopencv_imgproc \
    -lopencv_intensity_transform \
    -lopencv_line_descriptor \
    -lopencv_mcc \
    -lopencv_ml \
    -lopencv_objdetect \
    -lopencv_optflow \
    -lopencv_phase_unwrapping \
    -lopencv_photo \
    -lopencv_plot \
    -lopencv_quality \
    -lopencv_rapid \
    -lopencv_reg \
    -lopencv_rgbd \
    -lopencv_saliency \
    -lopencv_shape \
    -lopencv_stereo \
    -lopencv_stitching \
    -lopencv_structured_light \
    -lopencv_superres \
    -lopencv_surface_matching \
    -lopencv_text \
    -lopencv_tracking \
    -lopencv_video \
    -lopencv_videoio \
    -lopencv_videostab \
    -lopencv_wechat_qrcode \
    -lopencv_xfeatures2d \
    -lopencv_ximgproc \
    -lopencv_xobjdetect \
    -lopencv_xphoto

RUN mkdir build && mv tp /workspace/build/tp
