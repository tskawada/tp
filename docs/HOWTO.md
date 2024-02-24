# Tips and Setting guide

**tp** is a very simple command line tool. You only need to keep a few important points in mind to get the most out of it.

## 1. Preprocessing
Exposure changes should be kept gradual, especially for Holy Grail time-lapse sequence. Deflicker is also important. You can see them in the video below. In short, careful preprocessing produces excellent results.

https://github.com/tskawada/tp/assets/94617881/30762c51-18da-4304-bc8a-a4528c4c8a30

The images will be placed in any folder as follows:
```
[input_folder]
  ├── xxx.jpg
  ├── yyy.jpg
  ├── zzz.jpg
  ...
```
Automatically sorted based on exif data.

## 2. How to use Afterimage mode
Time-lapse with afterimage mode is not the best option for all sequences. This mode is useful, for example, for creating star trail movies by leaving star images.

### Afterimage level setting
**threshold** defines the degree of difference in brightness to be synthesized when performing comparative brightness compositing. The optimal value for this parameter varies depending on the footage, but based on my experience, it is recommended to set it in the range of 10-50.  
**alpha** sets how dark the past frames will be. The larger the value, the shorter the trajectory of the stars. 0-5 is recommended.

### Changes in the work according to Afterimage level
All footage is set to threshold=20. The following video illustrates the change in footage with alpha.
- alpha=0.1
- alpha=0.5
- alpha=1.0
- alpha=2.0

https://github.com/tskawada/tp/assets/94617881/d03e91be-6290-4c3b-9673-cbb088cde09d

