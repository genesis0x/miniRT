/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:18:38 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:23:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_clear_split(char **ptr)
{
    int i;

    i = 0;
    while (ptr[i])
    {
        free(ptr[i]);
        i++;
    }
	free(ptr);
    ptr = NULL;
}

t_list  *get_anim(t_canvas *canvas, t_list **anim)
{
    if (!canvas)
        return (*anim);
    if (!(canvas->img))
    {
        free (canvas);
        return (*anim);
    }
    ft_lstadd_back(anim, ft_lstnew(canvas));
    return (*anim);
}

void    check_textures(char *line, t_data *data)
{
    char    **arr;
    
    arr = ft_split(line, ' ', 0, 0);
    if (!arr)
    {
        free(line);
        dprintf(2, "Allocation Failed\n");
        exit (1); // to be changed
    }
    if (!strncmp(arr[0], "NO", 3))
        data->textures.north = get_anim(mlx_load_img(data->mlx.mlx_ptr, arr[1]), &data->textures.north);
    else if (!strncmp(arr[0], "SO", 3))
        data->textures.south = get_anim(mlx_load_img(data->mlx.mlx_ptr, arr[1]), &data->textures.south);
    else if (!strncmp(arr[0], "EA", 3))
        data->textures.east = get_anim(mlx_load_img(data->mlx.mlx_ptr, arr[1]), &data->textures.east);
    else if (!strncmp(arr[0], "WE", 3))
        data->textures.west = get_anim(mlx_load_img(data->mlx.mlx_ptr, arr[1]), &data->textures.west);
    else if ((!strncmp(arr[0], "F", 2) && data->textures.floor == -1) || (!strncmp(arr[0], "C", 2) && data->textures.ceiling == -1))
        get_cf_color(arr, data);
    else
    {
        ft_clear_split(arr);
        ft_error(inv_map);
    }
    ft_clear_split(arr);
    //for (int i = 0; arr[i]; i++)
      //  printf("%s\n", arr[i]);
}

void    read_map(char *filename, t_data *data)
{
    char    *line[2];
    int     n[1];

    n[0] = -1;
    data->fd = open(filename, O_RDONLY);
    if (data->fd < 0)
        ft_error(inv_file);
    while (-42)
    {
        line[0] = get_next_line(data->fd);
        if (!line[0])
            break ;
        line[1] = ft_strtrim(line[0], " ");
        printf("%s", line[1]);
        free(line[0]);
        if (line[1] && ++n[0] < 6)
            check_textures(line[1], data);
        else if (line[1] || n[0] >= 6)
            data->map = extend_matrix(data->map, line[1]);
        if (ft_strlen(line[1]) > data->width)
            data->width = strlen(line[1]);
        free(line[1]);
    }
    data->height = array_length(data->map);
}
