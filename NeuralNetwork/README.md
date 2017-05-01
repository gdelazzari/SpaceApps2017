## Live fire recognition Neural Network

The neural network is built using the FANN library ([download here](http://leenissen.dk/fann/wp/download/)), so you'll have to install it before compiling the code.

Also note that all the development has been done on Linux.

You'll have to create this directories with the video data:
+ `frames` here you will put all your video frames (named `<n>.jpg`, where <n> is the number of the frame)
+ `traindata` here you will put 3/4 frames to use as training data, each one with its corresponding `<n>_target.jpg` file, that must be of the same size and be a 4 color JPG image, with the nature parts represented in green (#00FF00), the fire parts in red (#FF0000), the smoke parts in blue (#0000FF) and the sky in black (#000000). Refer to the image below for an example
+ `output` that will be filled with the generated video overlay frames

When you run `make` four programs will be compiled which are, in order of usage:

+ **build_dataset** will take all the data from the `traindata` directory and create a `dataset.data` file containing the labeled training data for the NN
+ **train** will train the neural network using `dataset.data` and save the network (with all the calculated weights) as `network.net`
+ **test** will test the network on a couple of frames and show as ASCII graphics a quick view of how it's performing
+ **generate_video_overlay** will use the trained network to create the video overlay (720p resolution, so 1280x720 images) and output the frames in the `output` directory

You can then use the `compilevideo.sh` script to generate an MP4 video from the bitmap images in the `output` folder. Then use a video editing software to overlap the two videos, making the generated overlay a bit transparent.

Also note that there are a lot of `#define` directives you'll probably want to change, mainly for the number of frames you have but also for the number of samples to generate from each training image, etc...

This is an example `_target.jpg` image file used to train the network on a specific frame:
![](https://github.com/gdelazzari/SpaceApps2017/raw/master/Images/nn_target_example.jpg)
