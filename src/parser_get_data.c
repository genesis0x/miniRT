/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:09:14 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:23:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"


int get_data(t_data *data, t_parser *parser)
{
    char    *line[2];
    int     n[1];
    
    (void)data;
    n[0] = 0;
    while ((line[0] = get_next_line(parser->fd_cub)))
    {
        line[0] = ft_strtrim(line[0], " ");
        //printf("%s", line[1]);
        //free(line[0]);
        if (n[0] < 6)
        {
            if (get_elem(data, parser, line[0]) == 1)
                 n[0]++;
            else
            {
                free(line[0]);
            //     return (print_error(EXIT_FAILURE));
            }
        }
        else
        {
            line[1] = ft_strtrim(line[0], " ");
            free(line[0]);
            printf("%s", line[1]);
            //return (get_mapdata(data, parser, line[1]));
        }
        //free(line[0]);
    }
    return (EXIT_FAILURE);
}

/**************************************************************/
