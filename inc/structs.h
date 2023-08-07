/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:22:55 by hahadiou          #+#    #+#             */
/*   Updated: 2023/07/31 13:17:02 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "utils.h"

typedef struct s_mlx        t_mlx;
typedef struct s_vec3       t_vec3;
typedef struct s_ray        t_ray;
typedef struct s_sphere     t_sphere;
typedef struct s_light      t_light;
typedef struct s_hit_record t_hit_record;

struct s_mlx {
    void *mlx_ptr;
    void *win_ptr;
};

struct s_vec3
{
    double x;
    double y;
    double z;
    // Add new member for orientation (rotation)
    double orientation_x;
    double orientation_y;
    double orientation_z;
};


struct s_ray {
    t_vec3 origin;
    t_vec3 direction;
};

struct s_sphere {
    t_vec3 center;
    double radius;
    double orientation_x;
    double orientation_y;
    double orientation_z;
};

struct s_hit_record {
    t_vec3 point;
    t_vec3 normal;
    double  t;
};

struct s_light {
    t_vec3 position;
    t_vec3 color;
};


#endif // STRUCTS_H
