/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:21:40 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:23:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char    **square_map(t_data *data)
{
    char    **arr;
    int     i;
    int     j;

    arr = (char **)malloc(sizeof(char *) * (data->height + 1));
    j = -1;
    while (++j < data->height)
    {
        arr[j] = (char *)malloc(sizeof(char) * (data->width + 1));
        i = -1;
        while (++i < data->width)
        {
            if (i >= ft_strlen(data->map[j]))
                arr[j][i] = ' ';
            else
                arr[j][i] = data->map[j][i];
        }
        arr[j][i] = 0;
    }
    arr[j] = 0;
    return (arr);
}
