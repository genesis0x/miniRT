/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:09:54 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 10:45:16 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

int main(int ac, char **av)
{
    t_data  *data;
    if (ac != 2)
        return (1);
    init(data);
    parse_scene(data->scene, av[1]);
    
    mlx_loop(data->mlx->mlx);
	mlx_terminate(data->mlx->mlx);
    return (0);
}
