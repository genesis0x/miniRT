/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:22:55 by hahadiou          #+#    #+#             */
/*   Updated: 2023/07/19 19:36:11 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "utils.h"

typedef struct s_mlx        t_mlx;
typedef struct s_vec3       t_vec3;
typedef struct s_ray        t_ray;
typedef struct s_sphere     t_sphere;
typedef struct s_hit_record t_hit_record;

struct s_mlx {
    void *mlx_ptr;
    void *win_ptr;
};

struct s_vec3 {
    double x;
    double y;
    double z;
};

struct s_ray {
    t_vec3 origin;
    t_vec3 direction;
};

struct s_sphere {
    t_vec3 center;
    double radius;
};

struct s_hit_record {
    t_vec3 point;
    t_vec3 normal;
};


#endif // STRUCTS_H