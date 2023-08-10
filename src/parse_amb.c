/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_amb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:30:12 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 10:30:19 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

void	parse_amb(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 3)
		dprintf(2, "Invalid Number of args in param : %s\n", split[0]);
	stod(split[1], &(scene->amb.brightness));
	parse_color(split[2], &(scene->amb.color));
	scene->amb.color = color_scale(scene->amb.brightness, scene->amb.color);
	scene->amb.set = true;
}
