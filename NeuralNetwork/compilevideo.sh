#!/bin/sh

ffmpeg -framerate 25 -i output/%d.bmp -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p output_overlay.mp4
