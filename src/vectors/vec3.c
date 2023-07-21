/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:11:18 by hahadiou          #+#    #+#             */
/*   Updated: 2023/07/15 15:11:33 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

t_vec3	vec3(double x, double y, double z)
{
	t_vec3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}