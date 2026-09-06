/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Eloísa & Rick <minishell@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 by Eloísa & Rick            #+#    #+#             */
/*   Updated: 2026/03/23 by Eloísa & Rick           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Duplicate string up to n characters
 * 
 * @param s String to duplicate
 * @param n Maximum characters to copy
 * @return char* New string, NULL on error
 */
char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;
	size_t	copy_len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (n < len)
		copy_len = n;
	else
		copy_len = len;
	dup = malloc(copy_len + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, copy_len + 1);
	return (dup);
}