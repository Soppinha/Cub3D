/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <lcosta-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:58:36 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/07/22 19:00:25 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	get_trim_start(char const *s, char const *set)
{
	int	i;

	i = 0;
	while (s[i] && is_in_set(s[i], set))
		i++;
	return (i);
}

static int	get_trim_end(char const *s, char const *set)
{
	int	len;

	len = ft_strlen((char *)s);
	while (len > 0 && is_in_set(s[len - 1], set))
		len --;
	return (len);
}

static char	*return_empty_string(void)
{
	char	*trimmed;

	trimmed = malloc(1);
	if (!trimmed)
		return (NULL);
	trimmed[0] = '\0';
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;
	char	*trimmed;

	if (!s1)
		return (NULL);
	if (!set || !*set)
		return (ft_strdup(s1));
	start = get_trim_start(s1, set);
	if (start == ft_strlen((char *)s1))
		return (return_empty_string());
	end = get_trim_end(s1, set);
	len = end - start;
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_memcpy(trimmed, s1 + start, len);
	trimmed[len] = '\0';
	return (trimmed);
}
