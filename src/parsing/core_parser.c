/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:50:14 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:23:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"
/*******************************************************************************/

static void    help(int exit_status)
{
    dprintf(2, "usage: ./cub3D <map.cub>\n");
    exit (exit_status);
}

void ft_error(t_error error)
{
    dprintf(2, "%.*s", 28 * (error == inv_ac), "invalid number of arguments\n");
    dprintf(2, "%.*s", 20 * (error == inv_file), "error opening file: \n");
    dprintf(2, "%.*s", 26 * (error == inv_ext), "file must be of .cub type\n");
    dprintf(2, "%.*s", 12 * (error == inv_map), "invalid map\n");
    dprintf(2, "%.*s", 28 * (error == inv_wall), "map not surrounded by walls\n");
    if (error == inv_ac)
        help(EXIT_FAILURE);
    if (error == end)
       exit (EXIT_SUCCESS);
    exit (EXIT_FAILURE);
}

void    check_args(int ac, char **av, t_parser *parser)
{
    if (ac != 2)
    {
        ft_error(inv_ac);
    }
    if (!strncmp(".cub", av[1], 4))
    {
        ft_error(inv_ext);
    }
    parser->fd_cub = open(av[1], O_RDONLY);
    if (parser->fd_cub < 0)
        ft_error(inv_file);
}
/*****************************************************************************/

void    init(t_data *data, t_parser *parser)
{
    data->mms = 0;
    data->max.x = 0;
    data->max.y = 0;
    data->walls = calloc(4, sizeof(t_wall));
    // to protect malloc
    data->planes = calloc(2, sizeof(unsigned int));
    // to protect malloc
    parser->maplst = NULL;
    parser->map = NULL;
    parser->wall_check = calloc(2, sizeof(bool));
    // to protect malloc
}

void parse(int ac, char **av, t_data *data)
{
    t_parser    parser[1];

    check_args(ac, av, parser);
    init(data, parser);
    get_data(data, parser);
}
