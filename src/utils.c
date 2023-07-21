/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:53:18 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:23:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int array_length(char **arr)
{
    int  len;
    
    len = 0;
    if (!arr)
        return (0);
    while (arr[len])
        len++;
    return (len);
}

char	**extend_matrix(char **in, char *newstr)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	out = NULL;
	if (!newstr)
		return (in);
	len = array_length(in);
	out = (char **)malloc(sizeof(char *) * (len + 2));
	out[len + 1] = 0;
	if (!out)
		return (in);
	while (++i < len)
	{
		out[i] = strdup(in[i]);
		if (!out[i])
		{
			ft_clear_split(in);
			ft_clear_split(out);
		}
	}
	out[i] = strdup(newstr);
	//ft_clear_split(in);
	return (out);
}

int create_trgb(t_color c)
{
    int trgb = 0;
    trgb |= (c.t << 24) & 0xFF000000;
    trgb |= (c.r << 16) & 0x00FF0000;
    trgb |= (c.g << 8) & 0x0000FF00;
    trgb |= c.b & 0x000000FF;
    return trgb;
}

int	cub_atoi(char *nptr, long *nbr)
{
	*nbr = 0;
	if (!nptr || !isdigit(*nptr))
		return (-1);
	while (isdigit(*nptr))
	{
		*nbr = 10 * (*nbr) + (*nptr - '0');
		if (*nbr < 0 || *nbr > 255)
			return (-1);
		nptr++;
	}
	if (*nptr)
		return (-1);
	return (0);
}

void	get_cf_color(char **arr, t_data *data)
{
	char	**fc;
	int		str[2];
	int		c[3];
	t_color	aux;

	aux.t = 0;
	str[0] = !strncmp(arr[0], "F", 2);
	str[1] = !strncmp(arr[0], "C", 2);
	fc = ft_split(arr[1], ',', 0, 0);
	if (!fc || array_length(fc) != 3)
	{
		ft_clear_split(fc);
		return ;
		//ft_free_matrix(&fc);
	}
	c[0] = cub_atoi(fc[0], &aux.r);
	c[1] = cub_atoi(fc[1], &aux.g);
	c[2] = cub_atoi(fc[2], &aux.b);
	//ft_free_matrix(&fc);
	if (c[0] || c[1] || c[2])
		return ;
	if (str[0])
        data->textures.floor = create_trgb(aux);
	else if (str[1])
		data->textures.ceiling = create_trgb(aux);
}
