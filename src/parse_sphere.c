/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:31:07 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 10:38:25 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

static t_sphere *create_sphere_node()
{

	t_sphere *new_node = (t_sphere *)malloc(sizeof(t_sphere));
    if (new_node == NULL) {
        return NULL;
    }
	new_node->next = NULL;
    return (new_node);
}

static void add_sphere_to_back(t_sphere **lst, t_sphere *new_node)
{
    if (*lst == NULL) 
        *lst = new_node;
	else 
	{
        t_sphere *current = *lst;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void	parse_sphere(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 3)
		dprintf(2, "Invalid Number of args in param %s: \n", split[0]);
	t_sphere *new_sphere = create_sphere_node();
	parse_vec3(split[1], &(new_sphere->center));
	stod(split[2], &(new_sphere->radius));
	parse_color(split[3], &(new_sphere->color));
	new_sphere->radius = new_sphere->radius / 2.0;
	new_sphere->set = true;
	add_sphere_to_back(&(scene->object.sp_lst), new_sphere);
}
