# include "minirt.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define RAY_LENGTH 300

typedef struct {
    double x;
    double y;
} Point;

static mlx_image_t* image;

void drawRay(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int steps = dx > dy ? dx : dy;
    double xInc = (double)(x2 - x1) / steps;
    double yInc = (double)(y2 - y1) / steps;

    for (int i = 0; i <= steps; i++) {
		mlx_put_pixel(image, x1 + i * xInc, y1 + i * yInc, 0xFFFFFF);
        // mlx_pixel_put(mlx_ptr, win_ptr, x1 + i * xInc, y1 + i * yInc, 0xFFFFFF);
    }
}

int main() {

	mlx_t*	mlx;
	mlx = mlx_init(WIDTH, HEIGHT, "Ray Tracing", true);

	image = mlx_new_image(mlx, WIDTH, HEIGHT);


    Point origin = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

    while (1) {

        // Draw rays
        for (int angle = 0; angle < 360; angle += 5) {
            double radian = angle * M_PI / 180.0;
            int x2 = origin.x + (int)(RAY_LENGTH * cos(radian));
            int y2 = origin.y + (int)(RAY_LENGTH * sin(radian));
            drawRay(origin.x, origin.y, x2, y2);
        }

        mlx_put_pixel(image, origin.x, origin.y, 0xFFFFFF);
        
    }
	mlx_image_to_window(mlx, image, 0, 0);

    mlx_loop(mlx); // Keep the window open and continue handling events
	mlx_terminate(mlx);
    return 0;
}
