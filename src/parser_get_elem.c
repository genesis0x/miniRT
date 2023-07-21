/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:09:52 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:23:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"


int get_elem(t_data *data, t_parser *parser, char *line)
{
    (void)data;
    (void)parser;
    char    **textures;

    textures = ft_split(line, ' ', 0, 0);
    if (!textures)
    {
        free(line);
        dprintf(2, "No Memory\n");
        exit (EXIT_FAILURE); // to be changed
    }
    printf("%s\n", textures[0]);
    if (!strncmp(textures[0], "NO", 3))
        return (get_wall(parser, line, NO, &data->walls[NO]));
    else if (!strncmp(textures[0], "SO", 3))
        return (get_wall(parser, line, SO, &data->walls[SO]));
    else if (!strncmp(textures[0], "WE", 3))
        return (get_wall(parser, line, WE, &data->walls[WE]));
    else if (!strncmp(textures[0], "EA", 3))
        return (get_wall(parser, line, EA, &data->walls[EA]));
    // else if (!strncmp(textures[0], "C", 2))
    //     return (get_plane(parser, line, C, &data->planes[C]));
    // else if (!strncmp(textures[0], "F", 2))
    //     return (get_plane(parser, line, F, &data->planes[F]));
    // else if (textures[0][0] != '\n')
    //     ft_error(inv_map);
   // else
        //ft_error(inv_map);
    return (1);
}
