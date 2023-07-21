/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:44:58 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:23:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"


int get_wall(t_parser *parser, char *line, t_wall_enum wall_e, t_wall *wall)
{
    int n[1];

    n[0] = 0;
    if (parser->wall_check[wall_e] == false)
    {
        parser->wall_check[wall_e] = true;
        while (line[n[0]] && line[n[0]] != '\n')
        {
            if (n[0] < 3 || line[n[0]] == ' ')
                n[0]++;
            else
            {
                // if (access(trim_newline(&line[n[0]]), F_OK | R_OK) < 0)
                // {
                //     dprintf(2, "invalid texture path");
                //     exit (EXIT_FAILURE);
                // }
                wall->path = strdup(&line[n[0]]);
                if (!wall->path)
                    ft_error(inv_ac);
                return (1);
            }
        }
    }
    return (-1);
}
