/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:40:33 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 10:40:40 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

t_vec3 vec3_scale(t_vec3 vec, double scalar)
{
    return (t_vec3){vec.x * scalar, vec.y * scalar, vec.z * scalar};
}
