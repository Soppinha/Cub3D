/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <lcosta-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:35:56 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/07/22 18:58:44 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	i;

	dest_len = 0;
	while (dest[dest_len] && dest_len < size)
		dest_len++;
	i = 0;
	while (src[i])
		i++;
	src_len = i;
	if (size <= dest_len)
		return (dest_len + src_len);
	i = 0;
	while (i < src_len && i < (size - dest_len -1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (size > 0)
		dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
