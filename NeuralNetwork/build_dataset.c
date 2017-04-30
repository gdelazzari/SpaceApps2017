#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#define FRAME_NUM     3

#define CELL_SIZE     8

#define FRAME_W       160
#define FRAME_H       90
#define N             3

#define CELLS_X       (FRAME_W / CELL_SIZE)
#define CELLS_Y       ((FRAME_H - 2) / CELL_SIZE)

#define CELLS_PER_FRAME    50

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

int main(void) {
  srand(time(NULL));

  printf("Searching for frames\n");

  int count = 0;

  int target[CELLS_PER_FRAME * FRAME_NUM];

  for (int i = 0; i < FRAME_NUM; i++) {
    printf("%d\n", i);
    char filename[80];
    char filenameTrain[80];
    sprintf(filename, "traindata/%d.jpg", (i + 1));
    sprintf(filenameTrain, "traindata/%d_target.jpg", (i + 1));
    int x, y, n;
    int xt, yt, nt;
    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
    unsigned char *datatrain = stbi_load(filenameTrain, &xt, &yt, &nt, 0);
    if (x != FRAME_W || y != FRAME_H || n != N) {
      printf("Size of %s does not match\n", filename);
      return 1;
    }
    if (xt != FRAME_W || yt != FRAME_H || nt != N) {
      printf("Size of %s does not match\n", filenameTrain);
      return 1;
    }
    for (int j = 0; j < CELLS_PER_FRAME; j++) {
      int cx = rand() % CELLS_X;
      int cy = rand() % CELLS_Y;

      int tt = 0; // sky

      if (PIXEL(datatrain, xt, yt, (cx * 8 + 4), (cy * 8 + 4))[0] >= 250) {
        tt = 1; // fire
      }
      if (PIXEL(datatrain, xt, yt, (cx * 8 + 4), (cy * 8 + 4))[2] >= 250) {
        tt = 2; // smoke
      }
      if (PIXEL(datatrain, xt, yt, (cx * 8 + 4), (cy * 8 + 4))[1] >= 250) {
        tt = 3; // green
      }

      //if (tt != 0) {
        unsigned char* cropped = (unsigned char*) malloc(8 * 8 * 3);
        crop(data, cx * 8, cy * 8, 8, 8, cropped);
        char outfname[80];
        sprintf(outfname, "data/%d.bmp", count);
        stbi_write_bmp(outfname, 8, 8, 3, cropped);
        free(cropped);
        target[count] = tt;
        printf("Got sample at (%d, %d) on frame #%d, target = %d\n", cx, cy, i + 1, tt);
        count++;
      //} else {
        //printf("Ignored at (%d, %d)\n", cx, cy);
      //}
    }

    stbi_image_free(data);
  }

  printf("Crunching data and building dataset...\n");
  FILE* fout = fopen("dataset.data", "w+");
  if (!fout) {
    printf("Failed opening file for write\n");
    return 1;
  }
  fprintf(fout, "%d %d %d\n", count, (8 * 8 * 3), 4);
  for (int i = 0; i < count; i++) {
    char filename[80];
    sprintf(filename, "data/%d.bmp", i);
    int x, y, n;
    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
    for (int p = 0; p < (8 * 8 * 3); p++) {
      float v = (((float) (data[p])) / 255.f * 2.f) - 1.f;
      fprintf(fout, "%f ", v);
    }
    fprintf(fout, "\n");
    int out[4] = {-1, -1, -1, -1};
    out[target[i]] = 1;
    fprintf(fout, "%d %d %d %d\n", out[0], out[1], out[2], out[3]);
    stbi_image_free(data);
  }
  fclose(fout);
  printf("We did that boss\n");
  return 0;
}
