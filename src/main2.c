/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:05:55 by hahadiou          #+#    #+#             */
/*   Updated: 2023/07/31 19:12:22 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minirt.h"

#include <mlx.h>
#include <stdlib.h>
#include <math.h>

// Constants for the window dimensions
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Circle parameters
#define CIRCLE_RADIUS 20
#define CIRCLE_COLOR 0x00FF00 // Green color (change as you like)

// Global variables for the circle's position
int circle_x = WIN_WIDTH / 2;
int circle_y = WIN_HEIGHT / 2;
int circle_z = 0;

// Function to draw the circle
void draw_circle(void *mlx_ptr, void *win_ptr, int x, int y)
{
    mlx_pixel_put(mlx_ptr, win_ptr, x, y, CIRCLE_COLOR);
}

int main()
{
    // Initialize the minilibx
    void *mlx_ptr = mlx_init();
    if (!mlx_ptr)
        return -1;

    // Create a window
    void *win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Circle Window");
    if (!win_ptr)
        return -1;

    // Event loop to handle user input and draw the circle
    mlx_loop_hook(mlx_ptr, NULL, NULL); // Required to process events in the loop

    int should_exit = 0;
    while (!should_exit)
    {
        // Clear the window
        mlx_clear_window(mlx_ptr, win_ptr);

        // Draw the circle at its current position
        draw_circle(mlx_ptr, win_ptr, circle_x, circle_y);

        // Update the window to display the changes

        // Wait for user input or other events
        int key;
        switch (key)
        {
            case 27: // ESC key
                should_exit = 1;
                break;

            // Handle other keys for changing x, y, and z here
            // For example, you could increment or decrement the x, y, z values based on user input.
            // circle_x += ...;
            // circle_y += ...;
            // circle_z += ...;
        }
    }

    // Clean up and close the window
    mlx_destroy_window(mlx_ptr, win_ptr);
    free(mlx_ptr);

    return 0;
}


#include <mlx.h>
#include <stdlib.h>
#include <math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define CIRCLE_RADIUS 100
#define CIRCLE_COLOR 0x00FF00 // Green color (change as you like)

void mlx_put_pixel_to_image(int x, int y, int color, char *image_data)
{
    int bpp = 32; // Bits per pixel (32-bit color)
    int size_line = WIN_WIDTH * (bpp / 8); // Number of bytes per line
    char *pixel = image_data + (x * (bpp / 8)) + (y * size_line);
    *(int *)pixel = color;
}

static void draw_circle(int center_x, int center_y, int radius, char *image_data)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        mlx_put_pixel_to_image(center_x + x, center_y + y, CIRCLE_COLOR, image_data);
        mlx_put_pixel_to_image(center_x + y, center_y + x, CIRCLE_COLOR, image_data);
        mlx_put_pixel_to_image(center_x - y, center_y + x, CIRCLE_COLOR, image_data);
        mlx_put_pixel_to_image(center_x - x, center_y + y, CIRCLE_COLOR, image_data);
        mlx_put_pixel_to_image(center_x - x, center_y - y, CIRCLE_COLOR, image_data);
        mlx_put_pixel_to_image(center_x - y, center_y - x, CIRCLE_COLOR, image_data);
        mlx_put_pixel_to_image(center_x + y, center_y - x, CIRCLE_COLOR, image_data);
        mlx_put_pixel_to_image(center_x + x, center_y - y, CIRCLE_COLOR, image_data);

        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

static void draw_axes(void *mlx_ptr, void *win_ptr, char *image_data)
{
    int half_width = WIN_WIDTH / 2;
    int half_height = WIN_HEIGHT / 2;

    // Draw X-axis in red
    for (int x = 0; x < WIN_WIDTH; ++x)
        mlx_put_pixel_to_image(x, half_height, 0xFFFFFF, image_data);

    // Draw Y-axis in green
    for (int y = 0; y < WIN_HEIGHT; ++y)
        mlx_put_pixel_to_image(half_width, y, 0xF00FFFFF, image_data);

    // Draw Z-axis (circle) in blue
    int circle_center_x = half_width;
    int circle_center_y = half_height;
    draw_circle(circle_center_x, circle_center_y, CIRCLE_RADIUS, image_data);
}

int main()
{
    void *mlx_ptr = mlx_init();
    if (!mlx_ptr)
        return -1;

    void *win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Circle Window");
    if (!win_ptr)
        return -1;

    void *image = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    if (!image)
        return -1;

    char *image_data = mlx_get_data_addr(image, NULL, NULL, NULL);

    draw_axes(mlx_ptr, win_ptr, image_data);

    mlx_put_image_to_window(mlx_ptr, win_ptr, image, 0, 0);
    mlx_loop(mlx_ptr);

    mlx_destroy_image(mlx_ptr, image);
    mlx_destroy_window(mlx_ptr, win_ptr);
    mlx_destroy_display(mlx_ptr);
    free(mlx_ptr);

    return 0;
}
