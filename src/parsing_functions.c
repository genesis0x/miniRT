/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:22:58 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 10:26:36 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

void	parse_vec3(char *s, t_vec3 *vec3)
{
	char	**split;

	split = ft_split(s, ',');
	if (split == NULL)
		dprintf(2, "Inv Memory\n");
	stod(split[0], &(*vec3).x);
	stod(split[1], &(*vec3).y);
	stod(split[2], &(*vec3).z);
}

void	stod(char *s, double *res)
{
	int	i;

	i = 0;
	if ( s[1] && (s[0] == '+' || s[0] == '-' ) )
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '.')
		{
			dprintf(2, "Inv Number\n");
			exit (1);
		}
		i++;
	}
	*res = atof(s);
	if (s[0] == '+' || s[0] == '-')
		s = s + 1;
}

void	stoi(char *s, int min, int max, int *res)
{
	int	i;

	i = 0;
	if (s[0] && (s[0] == '+' || s[0] == '-'))
		i++;
	while (s[i])
	{
		// if (!ft_isdigit(s[i])) // TODO : to be modified and check the error
		// {
		// 	dprintf(2, "Inv Number stoi : %s\n", s);
		// 	exit (1);
		// }
		i++;
	}
	*res = ft_atoi(s);
	if (*res < min || *res > max)
		exit (1);
}

void	parse_color(char *s, t_vec3 *color)
{
	char	**split;
	int		primary;

	split = ft_split(s, ',');
	if (split == NULL)
	{
		dprintf(2, "Inv Memory");
		exit (1);
	}
	primary = 0;
	if (ft_array_len(split) != 3)
	{
		dprintf(2, "Inv number of args\n");
		exit (1);
	}
	stoi(split[0], 0, 255, &primary);
	(*color).x = (double)primary / 255.0;
	stoi(split[1], 0, 255, &primary);
	(*color).y = (double)primary / 255.0;
	stoi(split[2], 0, 255, &primary);
	(*color).z = (double)primary / 255.0;
}

t_vec3	color_scale(double f, t_vec3 c1)
{
	return ((t_vec3){f * c1.x, f * c1.y, f * c1.z});
}