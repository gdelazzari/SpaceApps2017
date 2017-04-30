#include <stdio.h>
#include "fann.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#define FRAME_NUM     75

#define CELL_SIZE     8

#define FRAME_W       160
#define FRAME_H       90
#define N             3

#define CELLS_X       (FRAME_W / CELL_SIZE)
#define CELLS_Y       ((FRAME_H - 2) / CELL_SIZE)

#define CELLS_PER_FRAME    20

#define OUTPUT_W      1280
#define OUTPUT_H      720

#define OUTPUT_CELL_SIZE  64

#define PIXEL(i, w, h, x, y)    ((unsigned char*) (i + (((y) * (w) * (N)) + ((x) * (N)))))

unsigned char* crop(unsigned char* image, int sx, int sy, int w, int h, unsigned char* result) {
  for (int x = sx; x < (sx + w); x++) {
    for (int y = sy; y < (sy + h); y++) {
      for (int c = 0; c < 3; c++) {
        PIXEL(result, w, h, (x - sx), (y - sy))[c] = PIXEL(image, FRAME_W, FRAME_H, x, y)[c];
      }
    }
  }
}

int main()
{
	struct fann *ann = fann_create_from_file("network.net");

  printf("Searching for frames\n");

  int count = 0;

  int target[CELLS_PER_FRAME * FRAME_NUM];

  for (int i = 0; i < FRAME_NUM; i++) {
    printf("[FRAME %d]\n", i);
    char filename[80];
    sprintf(filename, "frames/%d.jpg", (i + 1));
    char outfn[80];
    sprintf(outfn, "output/%d.bmp", (i + 1));
    int x, y, n;
    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
    if (x != FRAME_W || y != FRAME_H || n != N) {
      printf("Size of %s does not match\n", filename);
      return 1;
    }
    unsigned char* outimg = (unsigned char*) malloc(OUTPUT_W * OUTPUT_H * 3);
    for (int ox = 0; ox < OUTPUT_W; ox++) {
      for (int oy = 0; oy < OUTPUT_H; oy++) {
        PIXEL(outimg, OUTPUT_W, OUTPUT_H, ox, oy)[0] = 0;
        PIXEL(outimg, OUTPUT_W, OUTPUT_H, ox, oy)[1] = 0;
        PIXEL(outimg, OUTPUT_W, OUTPUT_H, ox, oy)[2] = 0;
      }
    }
    for (int cy = 0; cy < CELLS_Y; cy++) {
      for (int cx = 0; cx < CELLS_X; cx++) {
        unsigned char* cropped = (unsigned char*) malloc(8 * 8 * 3);
        crop(data, cx * 8, cy * 8, 8, 8, cropped);
        float input[8 * 8 * 3];
        for (int p = 0; p < (8 * 8 * 3); p++) {
          float v = (((float) (cropped[p])) / 255.f * 2.f) - 1.f;
          input[p] = v;
        }
      	float* out = fann_run(ann, input);

        uint8_t color[3] = {0, 0, 0};
        if (out[0] >= 0.5) {
          color[0] = 128;
          color[1] = 128;
          color[2] = 128;
        }
        if (out[1] >= 0.5) {
          color[0] = 255;
          color[1] = 64;
          color[2] = 0;
        }
        if (out[2] >= 0.5) {
          color[0] = 64;
          color[1] = 0;
          color[2] = 255;
        }
        if (out[3] >= 0.5) {
          color[0] = 0;
          color[1] = 255;
          color[2] = 0;
        }

        for (int ox = 0; ox < OUTPUT_CELL_SIZE; ox++) {
          for (int oy = 0; oy < OUTPUT_CELL_SIZE; oy++) {
            PIXEL(outimg, OUTPUT_W, OUTPUT_H, cx * OUTPUT_CELL_SIZE + ox, cy * OUTPUT_CELL_SIZE + oy)[0] = color[0];
            PIXEL(outimg, OUTPUT_W, OUTPUT_H, cx * OUTPUT_CELL_SIZE + ox, cy * OUTPUT_CELL_SIZE + oy)[1] = color[1];
            PIXEL(outimg, OUTPUT_W, OUTPUT_H, cx * OUTPUT_CELL_SIZE + ox, cy * OUTPUT_CELL_SIZE + oy)[2] = color[2];
          }
        }

        free(cropped);
      }
    }

    stbi_image_free(data);
    stbi_write_bmp(outfn, OUTPUT_W, OUTPUT_H, 3, outimg);
  }

	fann_destroy(ann);
	return 0;
}
