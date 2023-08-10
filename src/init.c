/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:36:21 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 10:07:42 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    init(t_data *data)
{
    data = calloc(1, sizeof(t_data));
    data->mlx->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
    data->mlx->image = mlx_new_image(data->mlx->mlx, WIDTH, HEIGHT);
}
