/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:05:55 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 09:55:26 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minirt.h"

static mlx_image_t* image;

t_vec3	vec3(double x, double y, double z)
{
	t_vec3 vec;
	
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 result;
	
	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

t_vec3	vec3_sub(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 result;
	
	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

t_vec3	vec3_mul(t_vec3 vec, double scalar)
{
	t_vec3 result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	result.z = vec.z * scalar;
	return (result);
}

// Function to apply translation to a t_vec3 entity
t_vec3 vec3_translate(t_vec3 vec, double tx, double ty, double tz)
{
    vec.x += tx;
    vec.y += ty;
    vec.z += tz;
    return vec;
}

// Function to apply rotation to a t_vec3 entity (in radians)
t_vec3 vec3_rotate(t_vec3 vec, double rx, double ry, double rz)
{
    // Apply rotation around the X-axis
    double cos_rx = cos(rx);
    double sin_rx = sin(rx);
    double new_y = vec.y * cos_rx - vec.z * sin_rx;
    double new_z = vec.y * sin_rx + vec.z * cos_rx;

    // Apply rotation around the Y-axis
    double cos_ry = cos(ry);
    double sin_ry = sin(ry);
    double new_x = vec.x * cos_ry + new_z * sin_ry;
    new_z = -vec.x * sin_ry + new_z * cos_ry;

    // Apply rotation around the Z-axis
    double cos_rz = cos(rz);
    double sin_rz = sin(rz);
    new_x = vec.x * cos_rz - new_y * sin_rz;
    new_y = vec.x * sin_rz + new_y * cos_rz;

    vec.x = new_x;
    vec.y = new_y;
    vec.z = new_z;

    return (vec);
}

t_vec3	ray_point_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_mul(ray.direction, t)));
}

double	vec3_dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3 vec3_cross(t_vec3 vec1, t_vec3 vec2)
{
    t_vec3 result;
    
    result.x = vec1.y * vec2.z - vec1.z * vec2.y;
    result.y = vec1.z * vec2.x - vec1.x * vec2.z;
    result.z = vec1.x * vec2.y - vec1.y * vec2.x;
    
    return (result);
}

int	vec3_to_rgb(t_vec3 color)
{
    int r = (int)(255.999 * color.x);
    int g = (int)(255.999 * color.y);
    int b = (int)(255.999 * color.z);
    
    return (r << 16) | (g << 8) | b;
}

t_ray	ray(t_vec3 origin, t_vec3 direction)
{
	t_ray r;
	
	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_hit_record	hit_record(t_vec3 point, t_vec3 normal)
{
	t_hit_record rec;
	
	rec.point = point;
	rec.normal = normal;
	return rec;
}

int		hit_sphere(t_sphere sphere, t_ray ray, double t_min, double t_max, t_hit_record *rec)
{
	t_vec3 oc = vec3_sub(ray.origin, sphere.center);
	
	double a = vec3_dot(ray.direction, ray.direction); // ray origin
	double b = 2.0 * vec3_dot(oc, ray.direction); // ray direction
	double c = vec3_dot(oc, oc) - sphere.radius * sphere.radius;
	
	double discriminant = b * b - 4 * a * c;
	
	if (discriminant > 0)
	{
		double root = sqrt(discriminant);
		double temp = (-b - root) / (2.0 * a);
		if (temp < t_max && temp > t_min)
		{
			rec->point = ray_point_at(ray, temp);
			rec->normal = vec3_mul(vec3_sub(rec->point, sphere.center), 1.0 / sphere.radius);
			return (1);
		}
		temp = (-b + root) / (2.0 * a);
		if (temp < t_max && temp > t_min)
		{
			rec->point = ray_point_at(ray, temp);
			rec->normal = vec3_mul(vec3_sub(rec->point, sphere.center), 1.0 / sphere.radius);
			return (1);
		}
	}
	return (0);
}

t_vec3 vec3_normalize(t_vec3 vec) {
    double length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    return vec3_mul(vec, 1.0 / length);
}

t_ray initialize_ray(t_vec3 origin, t_vec3 direction)
{
    t_ray r;
	
    r.origin = origin;
    r.direction = direction;
	
    return (r);
}

// Function to calculate the lighting contribution at a point from a light source
t_vec3 calculate_lighting(t_hit_record rec, t_vec3 light_pos, double light_brightness) {
    t_vec3 ambient_color = vec3(0.1, 0.1, 0.1); // Ambient color (grayish)
    t_vec3 diffuse_color = vec3(0.8, 0.6, 0.2); // Diffuse color (orange-ish)
    t_vec3 light_dir = vec3_sub(light_pos, rec.point);
    t_vec3 unit_light_dir = vec3_normalize(light_dir);

    // Calculate the Lambertian diffuse shading factor
    double diffuse = fmax(0.0, vec3_dot(rec.normal, unit_light_dir));

    // Calculate the final color with shading and light intensity
    t_vec3 ambient_lighting = vec3_mul(ambient_color, light_brightness);
    t_vec3 diffuse_lighting = vec3_mul(diffuse_color, light_brightness * diffuse);

    // Combine the ambient and diffuse lighting
    t_vec3 lighting_color = vec3_add(ambient_lighting, diffuse_lighting);

    return (lighting_color);
}

static void draw_ray(int start_x, int start_y, int target_x, int target_y)
{
    int dx = target_x - start_x;
    int dy = target_y - start_y;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float x_increment = (float)dx / steps;
    float y_increment = (float)dy / steps;

    float x = start_x;
    float y = start_y;

    for (int i = 0; i < steps; ++i)
    {
        mlx_put_pixel(image, round(x), round(y), 0XFFFFFFFF); // Color the line red (0xFF0000)
        x += x_increment;
        y += y_increment;
    }
}

static void draw_circle(int center_x, int center_y, int radius)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        mlx_put_pixel(image, center_x + x, center_y + y, 0xFFFFFFFF);
        mlx_put_pixel(image, center_x + y, center_y + x, 0xFFFFFFFF);
        mlx_put_pixel(image, center_x - y, center_y + x, 0xFFFFFFFF);
        mlx_put_pixel(image, center_x - x, center_y + y, 0xFFFFFFFF);
        mlx_put_pixel(image, center_x - x, center_y - y, 0xFFFFFFFF);
        mlx_put_pixel(image, center_x - y, center_y - x, 0xFFFFFFFF);
        mlx_put_pixel(image, center_x + y, center_y - x, 0xFFFFFFFF);
        mlx_put_pixel(image, center_x + x, center_y - y, 0xFFFFFFFF);

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

static void draw_axes(void)
{
    int half_width = 800 / 2;
    int half_height = 600 / 2;

    // Draw X-axis in blue
    for (int x = 0; x < 800; ++x)
        mlx_put_pixel(image, x, half_height, 0XFFFFFF);

    // Draw Y-axis in pink
    for (int y = 0; y < 600; ++y)
        mlx_put_pixel(image, half_width, y, 0XF00FFFFF);

    int circle_center_x = half_width - 350;
    int circle_center_y = half_height - 250;
    draw_circle(circle_center_x, circle_center_y, 20);
    
    int _x = half_width + 350;
    int _y = half_height + 250;
    draw_ray(circle_center_x, circle_center_y, _x, _y);
    draw_ray(circle_center_x, circle_center_y, _x+40, _y+40);
    draw_ray(circle_center_x, circle_center_y, _x+80, _y+40);
    // Draw Z-axis in blue
    // int diagonal_len = sqrt(800 * 800 + 600 * 600);
    // for (int d = 0; d < diagonal_len; ++d)
    // {
    //     int x = half_width + d * cos(M_PI / 4);
    //     int y = half_height + d * sin(M_PI / 4);
    //     mlx_put_pixel(image, x, y, 0xFF0000);
    //     // mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, x, y, 0x0000FF);
    // }
}

void draw_sphere(t_sphere sphere, t_vec3 light_pos, double light_brightness)
{
    t_vec3 lower_left_corner = vec3(-2.0, -1.5, -1.0);
    t_vec3 horizontal = vec3(4.0, 0.0, 0.0);
    t_vec3 vertical = vec3(0.0, 3.0, 0.0);
    t_vec3 origin = vec3(0.0, 0.0, 0.0);

    // Calculate the camera position, look_at, and direction based on the camera position and look-at point
    t_vec3 camera_position = vec3(0.0, 0.0, 0.0); // Move the camera to (0, 0, 0)
    t_vec3 look_at = vec3(0.0, 0.0, 1.0); // Look at the point (0, 0, 1)
    t_vec3 camera_direction = vec3_sub(look_at, camera_position);
    t_vec3 camera_right = vec3_cross(vec3(0.0, 1.0, 0.0), camera_direction);
    t_vec3 camera_up = vec3_cross(camera_direction, camera_right);

    for (int j = HEIGHT - 1; j >= 0; --j)
    {
        for (int i = 0; i < WIDTH; ++i)
        {
            double u = (double)i / WIDTH;
            double v = (double)j / HEIGHT;

            // Calculate the gradient background color based on the vertical position v
            t_vec3 background_color2 = vec3(1.0, 1.0, 1.0); // Upper color (light blue-ish)
            t_vec3 background_color1 = vec3(0.2, 0.2, 0.2); // Lower color (blue-ish)
            t_vec3 gradient_color = vec3_add(vec3_mul(background_color1, 1.0 - v), vec3_mul(background_color2, v));

            t_vec3 direction = vec3_add(lower_left_corner, vec3_add(vec3_mul(horizontal, u), vec3_mul(vertical, v)));

            // Apply translation and rotation to the direction vector
            direction = vec3_rotate(direction, sphere.orientation_x, sphere.orientation_y, sphere.orientation_z);

            t_ray ray = initialize_ray(origin, direction);

            t_hit_record rec;
            t_vec3 shading_color = vec3(0.0, 0.0, 0.0); // Initialize shading color to black

            if (hit_sphere(sphere, ray, 0.0, INFINITY, &rec))
            {
                // Calculate the surface normal
                t_vec3 normal = vec3_sub(rec.point, sphere.center);
                normal = vec3_normalize(normal);

                // Calculate the light direction vector
                t_vec3 light_dir = vec3_sub(light_pos, rec.point);
                light_dir = vec3_normalize(light_dir);

                // Calculate the Lambertian diffuse shading factor
                double diffuse = fmax(0.0, vec3_dot(normal, light_dir));

                // Calculate the reflection direction vector
                t_vec3 reflection_dir = vec3_sub(vec3_mul(normal, 2.0 * vec3_dot(light_dir, normal)), light_dir);
                reflection_dir = vec3_normalize(reflection_dir);

                // Calculate the specular reflection factor using Phong shading
                t_vec3 view_dir = vec3_sub(origin, rec.point);
                view_dir = vec3_normalize(view_dir);
                double specular = pow(fmax(0.0, vec3_dot(reflection_dir, view_dir)), 16); // Phong exponent of 16

                // Combine the ambient, diffuse, and specular components to get the shading color
                t_vec3 ambient_color = vec3(0.2, 0.2, 0.2); // Ambient color (grayish)
                t_vec3 diffuse_color = vec3(0.8, 0.6, 0.2); // Diffuse color (orange-ish)
                t_vec3 specular_color = vec3(1.0, 1.0, 1.0); // Specular color (white)

                // shading_color = vec3_add(shading_color, vec3_mul(ambient_color, 0.2)); // Add ambient lighting
                // shading_color = vec3_add(shading_color, vec3_mul(diffuse_color, light_brightness * diffuse));
                shading_color = vec3_add(shading_color, vec3_mul(specular_color, light_brightness * specular));
            }
            else
            {
                // Use the gradient background color if the ray doesn't hit the sphere
                shading_color = gradient_color;
            }
            // Set the pixel color based on the shading color
            mlx_put_pixel(image, i, HEIGHT - 1 - j, vec3_to_rgb(shading_color));
        }
    }
    draw_axes();
}

// Global variables to store the light position
// t_vec3 light_pos = vec3(-40.0, 50.0, 0.0);
t_vec3 light_pos = (t_vec3){
    .x=-40.0,
    .y=50.0,
    .z=0.0
};

t_sphere sphere = {
    .center = {0.0, 0.0, -2.6},
    .radius = 1.3
};

double light_brightness = 0.6;

mlx_t*	mlx;

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	printf("%d\n", image->instances[0].x);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
    {
        sphere.orientation_y += 0.1;		
        draw_sphere(sphere, light_pos, light_brightness);
        // image->instances[0].y -= 5;
    }
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
    {
        sphere.orientation_y -= 0.1;
        draw_sphere(sphere, light_pos, light_brightness);
		// image->instances[0].y += 5;
    }
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
    {
		// image->instances[0].x -= 5;
        light_pos.x -= 5.0; // Light moves horizontally within a range of -40 to 40
        light_pos.y -= 5.0; // Light moves vertically within a range of 50 to -50
        draw_sphere(sphere, light_pos, light_brightness);
    }
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
    {
		// image->instances[0].x += 5;
        light_pos.x += 5.0; // Light moves horizontally within a range of -40 to 40
        light_pos.y += 5.0; // Light moves vertically within a range of 50 to -50
        draw_sphere(sphere, light_pos, light_brightness);
    }
}

int		main(void)
{
	// t_sphere sphere;
	// mlx_t*	mlx;
    // t_vec3 light_pos;
    // double light_brightness;

	// sphere.center = vec3(0.0, 0.0, -2.6);
	// sphere.radius = 1.3;
    
    // Add the light source
    // light_pos = vec3(-40.0, 50.0, 0.0);
    // light_brightness = 0.6;
    
    sphere.orientation_x = 0.0;
    sphere.orientation_y = 0.0;
    sphere.orientation_z = 0.0;
    
    
	mlx = mlx_init(WIDTH, HEIGHT, "Sphere Ray Tracing", true);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);

    mlx_loop_hook(mlx, ft_hook, mlx);
	
    draw_sphere(sphere, light_pos, light_brightness);

	mlx_loop(mlx);
	mlx_terminate(mlx);

	return (0);
}
