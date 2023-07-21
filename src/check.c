/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:08:00 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:23:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void    check(int ac, char **av)
{
    int fd;
  
    if (ac != 2)
      ft_error(inv_ac);
    if (!strncmp(av[1], "--help", 6))
        help(EXIT_SUCCESS);
    fd = open(av[1], O_RDONLY);
    if (fd < 0)
      ft_error(inv_file);
    close(fd);
    if (!strncmp(".cub", av[1], 4))
    {
        //parser->error = inv_ext;
        ft_error(inv_ext);
    }
}
