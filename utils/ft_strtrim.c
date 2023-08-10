/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:45:08 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/10 10:52:50 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*str;

	i = -1;
	if (!s)
		return (0);
	if (start >= strlen(s))
	{
		return (calloc(1, 1));
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	while (++i < len)
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && strchr(set, *s1))
		++s1;
	len = ft_strlen(s1);
	while (len && strchr(set, s1[len]))
		len--;
	return (ft_substr(s1, 0, len + 1));
}
