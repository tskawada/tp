# tp

**tp** is a command line tool to generate (afterimage) time-lapse video from a sequence of jpg images.  
It generates uncompressed AVI files. Compression is usually required as a post-processing step by selecting an appropriate codec. 
[Any Video Converter](https://www.any-video-converter.jp/) is available as a free software.

[YouTube video](https://youtu.be/ZtHwgKmgkO4)

## Build and Run
```bash
sudo apt install libopencv-dev cmake
mkdir build
cd build
cmake ..
make
./tp /path/to/config/file
```
If necessary, please use the following command to install tp.
```bash
sudo make install
```

https://github.com/tskawada/tp/assets/94617881/6e48ffa0-13ba-4430-88b0-aa77a735bfb5

## Usage
All you need to prepare is a jpg images and a configuration file!

- Brightness adjustment and deflicker of jpg files must have been carried out beforehand. [LRTimelapse](https://lrtimelapse.com/) can be used for this.
- Comment out (#) is valid in the configuration file.
- In normal mode (mode: 0), alpha and threshold need not be specified. If specified, it is ignored.
```conf
input_folder=/path/to/input/
output_file=/path/to/output/movie.avi
fps=24.0           # frame per second
mode=0             # 0: normal, 1: afterimage
threshold=20       # Specifies the brightness threshold of the pixel to be synthesized in comparison brightness synthesis
alpha=1.0          # Specifies the afterimage level
```

## License
MIT License

## Author
[Kawada Yuta](https://kawadayuta.jp)  
There are several examples of this work. Not all use tp.

## Notes
### Tips and Setting guide
see [HOWTO.md](./docs/HOWTO.md)
