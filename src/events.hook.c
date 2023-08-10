/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:42:17 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 10:44:32 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

void ft_hook(t_data *data)
{
	mlx_t* mlx = param;

	// printf("%d\n", image->instances[0].x);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
    {
        data->scene->light->pos.y += 2.0;
		render_scene(data->scene);
        // image->instances[0].y -= 5;
    }
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
    {
		data->scene->light->pos.y -= 2.0;
		render_scene(data->scene);
		// image->instances[0].y += 5;
    }
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
    {
		// image->instances[0].x += 5;
		data->scene->light->pos.x -= 2.0;
		render_scene(data->scene);
    }
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
    {
		// image->instances[0].x += 5;
		data->scene->light->pos.x += 2.0;
		render_scene(data->scene);
    }
}

void    register_events(t_data *data)
{
    mlx_loop_hook(data->mlx->mlx, ft_hook, data);
}
