/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:30:40 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 10:37:23 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

static t_light	*create_light_node()
{
	t_light	*new_node = (t_light *)malloc(sizeof(t_light));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	return (new_node);
}

static void add_light_to_back(t_light **lst, t_light *new_node)
{
    if (*lst == NULL) 
        *lst = new_node;
	else 
	{
        t_light *current = *lst;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void	parse_light(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 4)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
	t_light	*new_light = create_light_node();
	parse_vec3(split[1], &(new_light->pos));
	stod(split[2], &(new_light->ratio));
	parse_color(split[3], &(new_light->color));
	new_light->color = color_scale(new_light->ratio, new_light->color);
	new_light->set = true;
	add_light_to_back(&scene->light, new_light);
}
