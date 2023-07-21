/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:13:10 by hahadiou          #+#    #+#             */
/*   Updated: 2023/07/15 15:13:29 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

t_vec3	vec3_sub(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 result;
    
	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}
