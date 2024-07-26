#ifndef UTILS_H
#define UTILS_H

#define VERSION "0.1.0"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define TICK_SPEED 5

#define WORLD_WIDTH 1280
#define WORLD_HEIGHT 1280

#define MAX_CAMERA_ZOOM 20
#define MIN_CAMERA_ZOOM 1

#define ZOOM_SPEED 20

#define NUM_NEIGHBORS 8

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int get_neighbors_count() {
  const int neighbors[NUM_NEIGHBORS][2] = {
      {-1, -1}, // Top-left
      {-1, 0},  // Top
      {-1, 1},  // Top-right
      {0, -1},  // Left
      {0, 1},   // Right
      {1, -1},  // Bottom-left
      {1, 0},   // Bottom
      {1, 1}    // Bottom-right
  };

  int count = 0;

  // for (int i = 0; i < WORLD_HEIGHT; i++) {
  // 	for (int j = 0; j < WORLD_WIDTH; j++) {
  // 		if ((*fb1)[i][j] == 0) {
  // 			int neighbors = 0;
  //
  // 			// right
  // 			if ((j + 1) < WORLD_WIDTH) {
  // 				if ((*fb1)[i][j+1]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// left
  // 			if ((j - 1) >= 0) {
  // 				if ((*fb1)[i][j-1]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// up
  // 			if (i - 1 >= 0) {
  // 				if ((*fb1)[i-1][j]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// down
  // 			if ((i + 1) < WORLD_HEIGHT) {
  // 				if ((*fb1)[i+1][j]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// diagonal top left
  // 			if ((i - 1 >= 0) && (j - 1) >= 0) {
  // 				if ((*fb1)[i-1][j-1]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// diagonal top right
  // 			if ((i - 1) >= 0 && (j + 1) < WORLD_WIDTH) {
  // 				if ((*fb1)[i-1][j+1]) {
  // 					neighbors++;
  // 				}
  // 			}
  // 			// diagonal bottom left
  // 			if ((i + 1) < WORLD_HEIGHT && (j - 1) >= 0) {
  // 				if ((*fb1)[i+1][j-1]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// diagonal bottom right
  // 			if ((i + 1) < WORLD_HEIGHT && (j + 1) < WORLD_WIDTH) {
  // 				if ((*fb1)[i+1][j+1]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			if (neighbors == 3) {
  // 				(*fb2)[i][j] = 1;
  // 			}
  //
  // 		} else {
  // 			int neighbors = 0;
  // 			// right
  // 			if ((j + 1) < WORLD_WIDTH) {
  // 				if ((*fb1)[i][j+1]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// left
  // 			if ((j - 1) >= 0) {
  // 				if ((*fb1)[i][j-1]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// up
  // 			if (i - 1 >= 0) {
  // 				if ((*fb1)[i-1][j]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// down
  // 			if ((i + 1) < WORLD_HEIGHT) {
  // 				if ((*fb1)[i+1][j]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// diagonal top left
  // 			if ((i - 1 >= 0) && (j - 1) >= 0) {
  // 				if ((*fb1)[i-1][j-1]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// diagonal top right
  // 			if ((i - 1) >= 0 && (j + 1) < WORLD_WIDTH) {
  // 				if ((*fb1)[i-1][j+1]) {
  // 					neighbors++;
  // 				}
  // 			}
  // 			// diagonal bottom left
  // 			if ((i + 1) < WORLD_HEIGHT && (j - 1) >= 0) {
  // 				if ((*fb1)[i+1][j-1]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// diagonal bottom right
  // 			if ((i + 1) < WORLD_HEIGHT && (j + 1) < WORLD_WIDTH) {
  // 				if ((*fb1)[i+1][j+1]) {
  // 					neighbors++;
  // 				}
  // 			}
  //
  // 			// Any live cell with fewer than two live neighbours dies, as if
  // caused by underpopulation. 			if (neighbors < 2) {
  // 				(*fb2)[i][j] = 0;
  // 			}
  //
  // 			// Any live cell with two or three live neighbours lives on to the
  // next generation. 			if (neighbors == 2 || neighbors == 3) {
  // 				(*fb2)[i][j] = 1;
  // 			}
  //
  // 			// Any live cell with more than three live neighbours dies, as if
  // by overpopulation. 			if (neighbors > 3) {
  // 				(*fb2)[i][j] = 0;
  // 			}
  //
  // 		}
  // 	}
  // }
  //
  return count;
}
#endif
