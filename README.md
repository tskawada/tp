# tp

**tp** is a command line tool to generate (afterimage) time-lapse video from a sequence of jpg images.  
It generates uncompressed AVI files. Compression is usually required as a post-processing step by selecting an appropriate codec. [Any Video Converter](https://www.any-video-converter.jp/) is available as a free software.

## How to build
```bash
sudo apt install libopencv-dev cmake
mkdir build
cd build
cmake ..
make
./tp
```

## Usage
All you need to prepare is a jpg images and a configuration file!

- Brightness adjustment and deflicker of jpg files must have been carried out beforehand. [LRTimelapse](https://lrtimelapse.com/) can be used for this.
- jpg filenames must be sorted in time order starting with 1.
- Comment out (#) is valid in the configuration file.
- In normal mode (mode: 0), level need not be specified. If specified, it is ignored.
```conf
input_folder=../data/from2/
output_folder=../data/to/
width=5872  # width of the image
height=3915  # height of the image
num_of_frames=200 
fps=24.0  # frame per second
mode=0  # 0: normal, 1: afterimage
level=10  # Specifies the afterimage level, minimum 0, maximum num_of_images
```

## License
MIT License

## Author
[Kawada Yuta](https://kawadayuta.jp)  
There are several examples of this work. Not all use tp.

## Notes
### TODO
- The width and height specifications are no longer required.
- Afterimage level is normalized from 0 to 100.
