/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:09:14 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:23:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

static char	*skip_empty_line(t_parser *parser, char *line)
{
	char	*temp_line;

	temp_line = ft_strdup(line);
	free(line);
	while (temp_line && temp_line[0] == '\n')
	{
		free(temp_line);
		temp_line = get_next_line(parser->fd_cub);
	}
	return (temp_line);
}

int	get_map(t_data *data, t_parser *par, char *line)
{
	char	*temp;

	temp = skip_empty_line(par, line);
	while (temp != NULL)
	{
		if (temp[0] == '\n')
			break ;
		if (temp[ft_strlen(temp) - 1] == '\n')
			temp[ft_strlen(temp) - 1] = '\0';
		if (ft_lstnew_back(&par->maplst, temp) == NULL)
		{
			ft_lstclear(&par->maplst, &free);
			free(temp);
			return (print_error("ft_lstnew_back error", EXIT_FAILURE));
		}
		save_max_length(data, temp);
		temp = get_next_line(par->fd_cub);
	}
	temp = skip_empty_line(par, temp);
	if (temp != NULL || data->max.y < 1)
	{
		free(temp);
		return (print_error("can only have one map", EXIT_FAILURE));
	}
	return (convert_map(data, par));
}

int	get_mapdata(t_data *data, t_parser *par, char *line)
{
	char	*temp;

	temp = check_invalid_line(par, line);
	if (temp == NULL)
    {
        ft_error(inv_map);
		//return (print_error("invalid map", EXIT_FAILURE));
    }
	if (get_map(data, par, temp))
		return (EXIT_FAILURE);
	if (set_map(data, par) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int get_data(t_data *data, t_parser *parser)
{
    char    *line[2];
    int n[1];
    
    n[0] = 0;
    while ((line[0] = get_next_line(parser->fd_cub)))
    {
        if (n[0] < 6)
        {
            if (get_elem(data, parser, line[0]) == 1)
                n[0]++;
            else
            {
                free(line[0]);
                return (print_error(EXIT_FAILURE));
            }
        }
        else
        {
            line[1] = ft_strtrim(line[0], " ");
            free(line[0]);
            return (get_mapdata(data, parser, line[1]));
        }
        free(line[0]);
    }
    return (EXIT_FAILURE);
}
