/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:09:54 by hahadiou          #+#    #+#             */
/*   Updated: 2023/07/20 16:51:40 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

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

t_vec3	ray_point_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_mul(ray.direction, t)));
}

double	vec3_dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
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

void draw_sphere(t_sphere sphere, void *mlx_ptr, void *win_ptr)
{
    t_vec3 lower_left_corner = vec3(-2.0, -1.5, -1.0);
    t_vec3 horizontal = vec3(4.0, 0.0, 0.0);
    t_vec3 vertical = vec3(0.0, 3.0, 0.0);
    t_vec3 origin = vec3(0.0, 0.0, 0.0);

    for (int j = HEIGHT - 1; j >= 0; --j)
    {
        for (int i = 0; i < WIDTH; ++i)
        {
            double u = (double)i / WIDTH;
            double v = (double)j / HEIGHT;
			
            t_vec3 direction = vec3_add(lower_left_corner, vec3_add(vec3_mul(horizontal, u), vec3_mul(vertical, v)));
            
			t_ray ray = initialize_ray(origin, direction);
			
            t_hit_record rec;
            
            // Calculate the background color as a gradient
            t_vec3 background_color = vec3(0.0, 0.0, 0.0);
            t_vec3 gradient_color_start = vec3(1.0, 1.0, 1.0);
            t_vec3 gradient_color_end = vec3(0.5, 0.7, 1.0);
            double t = 0.5 * (ray.direction.y + 1.0);
            background_color = vec3_add(vec3_mul(gradient_color_start, 1.0 - t), vec3_mul(gradient_color_end, t));
            
            if (hit_sphere(sphere, ray, 0.0, INFINITY, &rec))
            {
                // Calculate the surface normal
                t_vec3 normal = vec3_sub(rec.point, sphere.center);
                normal = vec3_mul(normal, 1.0 / sphere.radius);
                
                // Map the normal components to RGB values for visualization
                t_vec3 normal_color = vec3((normal.x + 1.0) / 2.0, (normal.y + 1.0) / 2.0, (normal.z + 1.0) / 2.0);
                
                // Set the sphere color based on the surface normal
                mlx_pixel_put(mlx_ptr, win_ptr, i, HEIGHT - 1 - j, vec3_to_rgb(normal_color));
            }
            else
            {
                // Set the background color
                mlx_pixel_put(mlx_ptr, win_ptr, i, HEIGHT - 1 - j, vec3_to_rgb(background_color));
            }
        }
    }
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_sphere sphere;

	sphere.center = vec3(0.0, 0.0, -1.0);
	sphere.radius = 0.5;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Sphere Ray Tracing");
	draw_sphere(sphere, mlx_ptr, win_ptr);
	mlx_loop(mlx_ptr);

	return (0);
}

