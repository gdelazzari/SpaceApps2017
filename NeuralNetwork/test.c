#include <stdio.h>
#include "fann.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define FRAME_NUM     3

#define CELL_SIZE     8

#define FRAME_W       160
#define FRAME_H       90
#define N             3

#define CELLS_X       (FRAME_W / CELL_SIZE)
#define CELLS_Y       ((FRAME_H - 2) / CELL_SIZE)

#define CELLS_PER_FRAME    20

#define PIXEL(i, w, h, x, y)    ((unsigned char*) (i + (((y) * (w) * (N)) + ((x) * (N)))))

void crop(unsigned char* image, int sx, int sy, int w, int h, unsigned char* result) {
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

  for (int i = 0; i < 10; i++) {
    printf("[FRAME %d]\n", i);
    char filename[80];
    sprintf(filename, "frames/%d.jpg", (i + 1));
    int x, y, n;
    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
    if (x != FRAME_W || y != FRAME_H || n != N) {
      printf("Size of %s does not match\n", filename);
      return 1;
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

        char o = ' ';
        if (out[0] >= 0.5) {
          o = '~';
        }
        if (out[1] >= 0.5) {
          o = '!';
        }
        if (out[2] >= 0.5) {
          o = '.';
        }
        if (out[3] >= 0.5) {
          o = '_';
        }

        printf("%c ", o);

        free(cropped);
      }
      printf("\n");
    }

    stbi_image_free(data);

    printf("\n");
  }

	fann_destroy(ann);
	return 0;
}
