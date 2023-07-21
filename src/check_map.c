/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:11:40 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:23:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


/*
The function first checks the cell to the left, top-left, and bottom-left of the given cell, 
and then checks the cell to the right, top-right, and bottom-right of the given cell. 
If any of these adjacent cells have an invalid wall, an error is raised using the cub_perror function with the error message inv_wall.
*/

void	check_walls(t_data *data, char **map, int i, int j)
{
	if (j - 1 >= 0 && j - 1 < data->height)
	{
		if (i - 1 >= 0 && i - 1 < ft_strlen(map[j - 1]))
            ft_error(inv_wall);
		if (i + 1 >= 0 && i + 1 < ft_strlen(map[j - 1]))
            ft_error(inv_wall);
		if (i >= 0 && i < ft_strlen(map[j - 1]))
            ft_error(inv_wall);
	}
	if (i - 1 >= 0 && i - 1 < ft_strlen(map[j]))
        ft_error(inv_wall);
	if (i + 1 >= 0 && i + 1 < ft_strlen(map[j]))
        ft_error(inv_wall);
	if (j + 1 >= 0 && j + 1 < data->height)
	{
		if (i - 1 >= 0 && i - 1 < ft_strlen(map[j + 1]))
            ft_error(inv_wall);
		if (i + 1 >= 0 && i + 1 < ft_strlen(map[j + 1]))
            ft_error(inv_wall);
		if (i >= 0 && i < ft_strlen(map[j + 1]))
            ft_error(inv_wall);
	}
}

int	ft_countchar(char *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

void    check_elements(t_data *data)
{
    int i;
    int j;
    
    j = -1;
    while (++j < data->height)
    {
        i = -1;
        while (++i < data->width)
        {
            if (data->map[j][i] == ' ')
                check_walls(data, data->map, i, j);
        }
    }
}

void    check_map(t_data *data)
{
    int i;
    int j;
    int w;

    j = -1;
    while (++j < data->height)
    {
        w = ft_strlen(data->map[j]) - 1;
        i = 0;
        while (data->map[j][i] == ' ' && i < w)
            i++;
        while (data->map[j][w] == ' ' && w > 0)
            w--;
        // if (strncmp(data->map[j], "", 1))
        //    ft_error(inv_map);
        if ((j == 0 || j == data->height - 1) && ft_strlen(data->map[j]) - ft_countchar(data->map[j], ' ') - ft_countchar(data->map[j], '1'))
           ft_error(inv_wall);
        else if (w > i && (data->map[j][i] != 1 || data->map[j][w] != 1))
           ft_error(inv_wall);
    }
    // to add a funtion that check elements
    check_elements(data);
}
