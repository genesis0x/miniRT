/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:07:22 by hahadiou          #+#    #+#             */
/*   Updated: 2023/07/20 17:19:32 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

t_vec3	vec3(double x, double y, double z);
t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3	vec3_mul(t_vec3 vec, double scalar);
t_vec3	vec3_sub(t_vec3 vec1, t_vec3 vec2);

double	vec3_dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3	ray_point_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_mul(ray.direction, t)));
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

void    draw_sphere(t_sphere sphere, t_mlx *mlx) {
    
    t_vec3 lower_left_corner = vec3(-2.0, -1.5, -1.0);
    t_vec3 horizontal = vec3(4.0, 0.0, 0.0);
    t_vec3 vertical = vec3(0.0, 3.0, 0.0);
    t_vec3 origin = vec3(0.0, 0.0, 0.0);

    for (int j = HEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < WIDTH; i++) {
            double x_Norm = (double)i / WIDTH;
            double y_Norm = (double)j / HEIGHT;

            t_vec3 direction = vec3_add(lower_left_corner, vec3_add(vec3_mul(horizontal, x_Norm), vec3_mul(vertical, y_Norm)));
            
            t_ray ray = {origin, direction};

            t_hit_record rec;

            if (hit_sphere(sphere, ray, 0.0, INFINITY, &rec)) {
                mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, i, HEIGHT - 1 - j, 0X0000FFFF);
            }
            else
                mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, i, HEIGHT - 1 - j, 0X000000);
        }
    }
}

int main( void ) {
    t_mlx   mlx[1];
    
    mlx->mlx_ptr = mlx_init();
    mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Rendring SPHERE");

    t_sphere    sphere;

    sphere.center = vec3(0.0, 0.0, -1.0); // center of sphere
    sphere.radius = 0.5; // radius of sphere
    
    draw_sphere(sphere, mlx);
    mlx_loop(mlx->mlx_ptr);
    
    return (0);
}
