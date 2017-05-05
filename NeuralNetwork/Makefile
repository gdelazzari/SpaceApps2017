LD = -lfann -lm
CFLAGS = -std=c99

ALL: build_dataset train test generate_video_overlay

build_dataset: build_dataset.c
	gcc -o build_dataset build_dataset.c $(LD) $(CFLAGS)

train: train.c
	gcc -o train train.c $(LD) $(CFLAGS)

test: test.c
	gcc -o test test.c $(LD) $(CFLAGS)

generate_video_overlay: generate_video_overlay.c
	gcc -o generate_video_overlay generate_video_overlay.c $(LD) $(CFLAGS)
