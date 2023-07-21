/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:10:35 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:23:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

int get_plane(t_parser *parser, char *line, t_plane plane_e, unsigned int *plane)
{
    int     n[0];
    int     color[3];
    char    **tmp;

    if (parser->color_check[plane_e] == true)
        return (-1);
    parser->color_check[plane_e] = true;
    tmp = ft_split(&line[2], ',', 0, 0);
    n[0] = -1;
    while (tmp[++n[0]])
    {
        if (set_to_rgb(n[0], tmp, color))
        {
            free (tmp); // to call clear_split function
            return (-1);
        }
    }
    free (tmp); // to call clear split function
    if (n[0] != 3)
        return (-1);
    *plane = make_color(color[0], color[1], color[2]);
    return (1);
}
