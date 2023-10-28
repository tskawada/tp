# High-speed optimization of tp using CUDA

Starting from version 2.0, **tp** supports image processing acceleration using CUDA. This has resulted in approximately a 24% reduction in processing time.

However, setting up the environment can be somewhat more complex compared to normal tp. Therefore, please use the CUDA-enabled tp environment built within a Docker container.

## How to use the GPU-accelerated tp
### 1. Build the Dockerfile
By building the provided Dockerfile, you can set up the following environment.

> Ubuntu 22.04 with CUDA 11.8.0 (runtime)  
> CUDA-enabled OpenCV 4.5.3

The following command is used for building.
```bash
cd tp && docker build -t tp-container .
```

### 2. Launching the Docker container
To utilize the GPU within the container, don't forget to include the `--gpus` option.
```bash
docker run -it --gpus all tp-container bash
```
Execute nvidia-smi inside the container to ensure that the GPU is properly recognized.

### 3. Running tp
Everything else is the same as usual. Place the jpg sequence and edit the config file accordingly. TP will return results more quickly!

## Benchmark
### Environment
> CPU: Intel(R) Core(TM) i5-9500 CPU @ 3.00GHz  
> GPU: NVIDIA GeForce RTX 3090 Ti  
> Memory: 32GB  

|           |   w/o CUDA   |     w/ CUDA    |
| --------- | :----------: | :------------: |
| time      | 5 min 32 sec |  4 min 12 sec  |
| reduction |      -       | **24% faster** |

## Technical discussion and todo
Only the part related to comparative brightness synthesis was implemented using CUDA in this release. The other parts still run on the CPU, and there is room for improvement in that aspect. Therefore, please note that when selecting mode 0, you should not expect any acceleration. Furthermore, we have not yet confirmed whether it operates successfully on GPUs of different models. Compatibility between machines and optimization issues require further investigation.  
Additionally, there is a need for considerations to make the Docker image more lightweight.
