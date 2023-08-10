/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:09:12 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 10:20:36 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

static int check_file(const char *filename, const char *ext)
{
    const char  *file_ext;
    size_t      ext_len;
    size_t      file_len;

    ext_len = strlen(ext);
    file_len = strlen(filename);
    file_ext = filename + (file_len - ext_len);
    if (file_len < ext_len)
        return (0);
    return (strcmp(file_ext, ext) == 0);
}

void	parse_ids(t_scene *scene, char **split)
{
	if (!strcmp(split[0], "C"))
		parse_cam(scene, split);
	else if (!strcmp(split[0], "A"))
		parse_amb(scene, split);
	else if (!strcmp(split[0], "L"))
		parse_light(scene, split);
	else if (!strcmp(split[0], "sp"))
		parse_sphere(scene, split);
	else if (!strcmp(split[0], "pl"))
		parse_plane(scene, split);
	else if (!strcmp(split[0], "cy"))
		parse_cylinder(scene, split);
	else
		dprintf(2, "Invalid Id\n");
}

int	parse_scene(t_scene *scene, char *filename)
{
	int		fd;
	char	*line[2];
	char	**split;

    check_file(filename, ".rt");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		dprintf(2, "Error opening file\n");
		return (1);
	}
	while (-42)
	{
		line[0] = get_next_line(fd);
		if (line[0] == NULL)
			break ;
		line[1] = ft_strtrim(line[0], " \t");
		split = ft_split(line[1], ' ');
		if (split == NULL)
		{
			dprintf(2, "Inv Memeory\n");
			exit (1);
		}
		parse_ids(scene, split);
	}
	return (0);
}
