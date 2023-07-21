/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:36:21 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:23:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    init_data(t_data *data)
{
    data->width = 0;
    data->height = 0;
    data->fd = -1;
    data->map = NULL;
    data->mlx.mlx_ptr = NULL;
    data->mlx.win_ptr = NULL;
    data->mlx.mlx_ptr = mlx_init();
    data->mlx.win_ptr = NULL;
    data->textures.floor = -1;
    data->textures.ceiling = -1;
    // data.mlx = (t_mlx *)malloc(sizeof(t_mlx));
    // data.canvas = (t_canvas *)malloc(sizeof(t_canvas));
    // data.textures = malloc(sizeof(t_list));
}
