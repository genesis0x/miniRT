/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:31:24 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 11:06:31 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

static t_plane *create_plane_node()
{

	t_plane *new_node = (t_plane *)malloc(sizeof(t_plane));
    if (new_node == NULL) {
        return NULL;
    }
	new_node->next = NULL;
    return (new_node);
}

static void add_plane_to_back(t_plane **lst, t_plane *new_node)
{
    if (*lst == NULL) 
        *lst = new_node;
	else 
	{
        t_plane *current = *lst;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void	parse_plane(t_scene *scene, char **split)
{
    t_plane *new_plane;
	if (ft_array_len(split) != 4)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
    new_plane = create_plane_node();
	parse_vec3(split[1], &(new_plane->point));
	parse_vec3(split[2], &(new_plane->normal));
	parse_color(split[3], &(new_plane->color));
    new_plane->set = true;
    add_plane_to_back(&(scene->object.pl_lst), new_plane);
}
