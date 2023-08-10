/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:29:33 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 10:29:47 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

void	parse_cam(t_scene *scene, char **split)
{
	t_vec3	look_at;
	
	if (scene->cam.set)
		dprintf(2, "Parsing Error in Camera\n");
	if (ft_array_len(split) != 4)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
	parse_vec3(split[1], &(scene->cam.pos));
	// printf("vec3: spt %s\n", split[1]);
	scene->cam.pos_initial = scene->cam.pos;
	parse_vec3(split[2], &look_at);
	// printf("vec3: spt %s\n", split[2]);
	scene->cam.dir = vec3_norm(vec3_sub(look_at, scene->cam.pos));
	scene->cam.dir_initial = scene->cam.dir;
	stoi(split[3], 1, 179, &(scene->cam.fov));
	scene->cam.set = true;
}
