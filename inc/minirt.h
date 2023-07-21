/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:02:02 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:20:54 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <math.h>
# include <string.h>

# include "structs.h"

#define WIDTH 800
#define HEIGHT 600

enum e_error t_error;

enum e_error {
    inv_ext,
    inv_file
};


void	ft_putstr_fd(char *s, int fd);

#endif // MINIRT_H
