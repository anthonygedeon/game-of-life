#include "utils.h"

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

typedef uint8_t (*matrix_ptr)[WORLD_HEIGHT][WORLD_WIDTH];

void draw_grid(int cell_size) {
	Color line_color =  { .r = 21, .g = 21, .b = 21 , .a = 255  };

	// draw horizontal lines
	for (int i = cell_size; i < WORLD_WIDTH; i += cell_size) {
		DrawLine(0, i, WORLD_WIDTH, i, line_color);
	}
	
	// draw vertical lines
	for (int i = cell_size; i < WORLD_HEIGHT; i += cell_size) {
		DrawLine(i, 0, i, WORLD_HEIGHT, line_color);
	}
}

// TODO: why do I have to wrap pointers in ()'s/ how exactly does this code work? And can I rewrite it 
// to be more flexible
// The () are necessary because the compiler would treat it as an array of pointers instead of a pointer that points to an array
void swap_buffers(uint8_t (**a)[WORLD_HEIGHT][WORLD_WIDTH], uint8_t (**b)[WORLD_HEIGHT][WORLD_WIDTH]) {
	uint8_t (*temp)[WORLD_HEIGHT][WORLD_WIDTH] = *a;
	*a = *b;
	*b = temp;
}

void clear(int height, int width, uint8_t fb[height][width]) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fb[i][j] = 0;
		}
	}
}

void draw(Rectangle pixels[], size_t size) {
	for (int i = 0; i < size; i++) {
		DrawRectangleRec(pixels[i], WHITE);
	}
}

Vector2 adjust_scroll_speed(float speed) {
	return Vector2Scale(GetMouseWheelMoveV(), speed);
}

Vector2 get_mouse_to_world(Camera2D camera) {
	return GetScreenToWorld2D(GetMousePosition(), camera);
}

void zoom_at_mouse_position(Camera2D* camera) {
	Vector2 before_zoom = get_mouse_to_world(*camera);

	// Apply zoom
	camera->zoom = Clamp(
			camera->zoom + GetMouseWheelMove() * ZOOM_SPEED * GetFrameTime(), 
			MIN_CAMERA_ZOOM, 
			MAX_CAMERA_ZOOM 
		);

	// Get the new mouse position in world coordinates after zoom
	Vector2 after_zoom = get_mouse_to_world(*camera);

	// Adjust the camera offset to keep the mouse position fixed
	camera->target.x += (before_zoom.x - after_zoom.x);
	camera->target.y += (before_zoom.y - after_zoom.y);		
}

void handle_scrolling(Camera2D* camera) {
	camera->target = Vector2Subtract(camera->target, adjust_scroll_speed(24.0f));
}

// TODO: breaks when zooming and scrolling right/bottom
void handle_camera_constraints(Camera2D* camera) {
	if (camera->target.x < camera->offset.x)
		camera->target.x = camera->offset.x;

	if (camera->target.x > WORLD_WIDTH - camera->offset.x)
		camera->target.x = WORLD_WIDTH - camera->offset.x;

	if (camera->target.y < camera->offset.y)
		camera->target.y = camera->offset.y;

	if (camera->target.y > WORLD_HEIGHT - camera->offset.y)
		camera->target.y = WORLD_HEIGHT - camera->offset.y;
}

int main(int argc, char* argv[]) {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life" " " VERSION);
    SetTargetFPS(60);           

	uint8_t fb_curr[WORLD_HEIGHT][WORLD_WIDTH];
	uint8_t fb_next[WORLD_HEIGHT][WORLD_WIDTH];

	matrix_ptr fb1 = &fb_curr;
	matrix_ptr fb2 = &fb_next;

	bool check_neighbors = false;
	bool step = false;
	bool erase = false;

	const float scroll_speed = 1.0;
	float cell = 2.0f;

	Rectangle pixels[10000];

	Camera2D camera = {
		.zoom = 2.0f,
		.target = (Vector2){ .x = (float)SCREEN_WIDTH / 2, .y = (float)SCREEN_HEIGHT / 2 },
		.offset = (Vector2){ .x = (float)SCREEN_WIDTH / 2, .y = (float)SCREEN_HEIGHT / 2 },
		.rotation = 0.0f
	};
	
	int tick_rate = 1;
	int tick_speed = TICK_SPEED;
	
    while (!WindowShouldClose()) {
		int pixel_size = 0;
		
		if (IsKeyDown(KEY_LEFT_CONTROL) && GetMouseWheelMove() != 0) {
			zoom_at_mouse_position(&camera);
		}  else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 virtual_mouse = get_mouse_to_world(camera);
			virtual_mouse.x = floor(virtual_mouse.x / cell);
			virtual_mouse.y = floor(virtual_mouse.y / cell);
			
			if (!erase) {
				(*fb1)[(int)virtual_mouse.y][(int)virtual_mouse.x] = 1;
			} else {
				(*fb1)[(int)virtual_mouse.y][(int)virtual_mouse.x] = 0;
			}
		} else if (GetMouseWheelMove() != 0){
			handle_scrolling(&camera);
			handle_camera_constraints(&camera);
		}

		if (IsKeyDown(KEY_UP)) {
			tick_rate += 1;

			if (tick_rate >= TICK_SPEED) {
				tick_rate = TICK_SPEED;
			}
		}

		if (IsKeyDown(KEY_DOWN)) {
			tick_rate -= 1;

			if (tick_rate <= 0) {
				tick_rate = 1;
			}
		}

		if (IsKeyPressed(KEY_E)) {
			erase = !erase;
		}

		if (IsKeyPressed(KEY_R)) {
			check_neighbors = true;
		}

		if (IsKeyPressed(KEY_P)) {
			check_neighbors = false;
		}

		if (IsKeyPressed(KEY_S)) {
			step = true;
		}

		if (IsKeyPressed(KEY_C)) {
			clear(WORLD_WIDTH, WORLD_HEIGHT, *fb1);
			check_neighbors = false;
			pixel_size = 0;
		}

		if (check_neighbors || step) {
			for (int i = 0; i < WORLD_HEIGHT; i++) {
				for (int j = 0; j < WORLD_WIDTH; j++) {
					if ((*fb1)[i][j] == 0) {
						int neighbors = 0;

						// right
						if ((j + 1) < WORLD_WIDTH) {
							if ((*fb1)[i][j+1]) {
								neighbors++;
							}
						}

						// left
						if ((j - 1) >= 0) {
							if ((*fb1)[i][j-1]) {
								neighbors++;
							}
						}

						// up
						if (i - 1 >= 0) {
							if ((*fb1)[i-1][j]) {
								neighbors++;
							}
						}

						// down
						if ((i + 1) < WORLD_HEIGHT) {
							if ((*fb1)[i+1][j]) {
								neighbors++;
							}
						}

						// diagonal top left
						if ((i - 1 >= 0) && (j - 1) >= 0) {
							if ((*fb1)[i-1][j-1]) {
								neighbors++;
							}
						}

						// diagonal top right
						if ((i - 1) >= 0 && (j + 1) < WORLD_WIDTH) {
							if ((*fb1)[i-1][j+1]) {
								neighbors++;
							}
						}
						// diagonal bottom left
						if ((i + 1) < WORLD_HEIGHT && (j - 1) >= 0) {
							if ((*fb1)[i+1][j-1]) {
								neighbors++;
							}
						}

						// diagonal bottom right
						if ((i + 1) < WORLD_HEIGHT && (j + 1) < WORLD_WIDTH) {
							if ((*fb1)[i+1][j+1]) {
								neighbors++;
							}
						}

						if (neighbors == 3) {
							(*fb2)[i][j] = 1;
						}

					} else {
						int neighbors = 0;
						// right
						if ((j + 1) < WORLD_WIDTH) {
							if ((*fb1)[i][j+1]) {
								neighbors++;
							}
						}

						// left
						if ((j - 1) >= 0) {
							if ((*fb1)[i][j-1]) {
								neighbors++;
							}
						}

						// up
						if (i - 1 >= 0) {
							if ((*fb1)[i-1][j]) {
								neighbors++;
							}
						}

						// down
						if ((i + 1) < WORLD_HEIGHT) {
							if ((*fb1)[i+1][j]) {
								neighbors++;
							}
						}

						// diagonal top left
						if ((i - 1 >= 0) && (j - 1) >= 0) {
							if ((*fb1)[i-1][j-1]) {
								neighbors++;
							}
						}

						// diagonal top right
						if ((i - 1) >= 0 && (j + 1) < WORLD_WIDTH) {
							if ((*fb1)[i-1][j+1]) {
								neighbors++;
							}
						}
						// diagonal bottom left
						if ((i + 1) < WORLD_HEIGHT && (j - 1) >= 0) {
							if ((*fb1)[i+1][j-1]) {
								neighbors++;
							}
						}

						// diagonal bottom right
						if ((i + 1) < WORLD_HEIGHT && (j + 1) < WORLD_WIDTH) {
							if ((*fb1)[i+1][j+1]) {
								neighbors++;
							}
						}

						// Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
						if (neighbors < 2) {
							(*fb2)[i][j] = 0;
						}

						// Any live cell with two or three live neighbours lives on to the next generation.
						if (neighbors == 2 || neighbors == 3) {
							(*fb2)[i][j] = 1;
						}

						// Any live cell with more than three live neighbours dies, as if by overpopulation.
						if (neighbors > 3) {
							(*fb2)[i][j] = 0;
						}

					}
				}
			}
		}

		for (int i = 0; i < WORLD_HEIGHT; i++) {
			for (int j = 0; j < WORLD_WIDTH; j++) {
				if ((*fb1)[i][j])  {
					pixels[pixel_size++] = (Rectangle){ 
						.width = cell, 
						.height = cell, 
						.x = j * cell, 
						.y = i * cell 
					};
				} 
				
			}
		}
		
        BeginDrawing();
            ClearBackground(BLACK);

			BeginMode2D(camera);
				if (tick_speed <= 0) {
					if (check_neighbors || step) {
						clear(WORLD_HEIGHT, WORLD_WIDTH, *fb1);
					}
				}

				draw(pixels, pixel_size);

				if (tick_speed <= 0) {
					if (check_neighbors || step) {
						swap_buffers(&fb1, &fb2);
					}

					step = false;
					tick_speed = TICK_SPEED;
				}
				draw_grid(cell);
			EndMode2D();
        EndDrawing();

		tick_speed -= tick_rate;

		if (tick_speed <= 0) {
			tick_speed = 0;
		}
    }

	CloseWindow();

    return 0;
}
