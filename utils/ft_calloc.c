/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:56:38 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/08 23:58:54 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*b;

	b = (char *)malloc(size * count);
	if (!b)
		return (NULL);
	ft_bzero(b, size * count);
	return (b);
}
