/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:31:36 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 11:07:15 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

static t_cylinder *create_cylinder_node()
{

	t_cylinder *new_node = (t_cylinder *)malloc(sizeof(t_cylinder));
    if (new_node == NULL) {
        return NULL;
    }
	new_node->next = NULL;
    return (new_node);
}

static void add_cylinder_to_back(t_cylinder **lst, t_cylinder *new_node)
{
    if (*lst == NULL) 
        *lst = new_node;
	else 
	{
        t_cylinder *current = *lst;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void	parse_cylinder(t_scene *scene, char **split)
{
    t_cylinder  *new_cylinder;
	if (ft_array_len(split) != 6)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
    new_cylinder = create_cylinder_node();
	parse_vec3(split[1], &(new_cylinder->center));
	parse_vec3(split[2], &(new_cylinder->axis));
	stod(split[3], &(new_cylinder->diameter));
	stod(split[4], &(new_cylinder->height));
	parse_color(split[5], &(new_cylinder->color));
	new_cylinder->set = true;
    add_cylinder_to_back(&(scene->object.cy_lst), new_cylinder);
}
