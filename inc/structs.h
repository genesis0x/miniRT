/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:22:55 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 10:04:16 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minirt.h"

typedef struct 	s_scene		t_scene;
typedef struct 	s_set		t_set;
typedef struct 	s_cam		t_cam;
typedef struct	s_vec3		t_vec3;
typedef struct	s_am_light	t_am_light;
typedef struct	s_light		t_light;
typedef struct	s_object	t_object;
typedef struct s_sphere		t_sphere;
typedef struct s_cylinder	t_cylinder;
typedef struct s_plane		t_plane;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct s_cam
{
	bool	set;
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	pos_initial;
	t_vec3	dir_initial;
	int		fov;
};

struct s_am_light
{
	bool	set;
	double	brightness;
	t_vec3	color;
};

struct s_light
{
	double	set;
	t_vec3	pos;
	double	ratio;
	t_vec3	color;
	t_light	*next;
};

struct s_sphere	
{
	t_vec3		center;
	double		radius;
	t_vec3		color;
	double		set;
	t_sphere	*next;
};

struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_vec3	color;
	double	set;
	t_plane	*next;
};

struct s_cylinder
{
    t_vec3 		center;
    t_vec3 		axis;
    double 		diameter;
    double		height;
    t_vec3 		color;
    double 		set;
	t_cylinder	*next;
};

struct s_object
{
	t_sphere	*sp_lst;
	t_cylinder	*cy_lst;
	t_plane		*pl_lst;
};

struct s_scene
{
	t_object	object;
	int			width;
    int			height;
    t_am_light 	amb;
    t_cam 		cam;
    t_light 	*light;
	t_plane		plane;
	t_cylinder	cylinder;
};

typedef struct s_mlx
{
	mlx_image_t		*image;
	mlx_t			*mlx;
}	t_mlx;

typedef struct s_data
{
	t_mlx	*mlx;
	t_scene	*scene;	
}	t_data;

#endif // STRUCTS_H
