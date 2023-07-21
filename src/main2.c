/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:05:55 by hahadiou          #+#    #+#             */
/*   Updated: 2023/07/19 19:57:05 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    ft_error(int error) {
    if (error == inv_ext) {
        ft_putstr_fd("file must be of .rt type\n", 2);
    }
    else if (error == inv_file) {
        ft_putstr_fd("error opening file: \n", 2);
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        dprintf(2, "Error\n");
        return (1);
    }
    
    if (!strncmp(av[1], ".rt", 4))
        ft_error(inv_ext);

    int fd = open(av[1], O_RDONLY);
    if (fd < 0)
        ft_error(inv_file);
    
    char *line;

    while ((line = get_next_line(fd))) {
        printf("%s", line);
    }
    free(line);
    
    return (0);
}
