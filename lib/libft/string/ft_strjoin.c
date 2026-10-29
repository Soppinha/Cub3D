/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <lcosta-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:43:15 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/07/22 18:58:34 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	if (len == 0)
	{
		joined = malloc(1);
		if (!joined)
			return (NULL);
		*joined = '\0';
		return (joined);
	}
	joined = malloc(len + 1);
	if (!joined)
		return (NULL);
	ft_memcpy(joined, s1, ft_strlen((char *)s1));
	ft_memcpy(joined + ft_strlen((char *)s1), s2, ft_strlen((char *)s2) + 1);
	return (joined);
}
