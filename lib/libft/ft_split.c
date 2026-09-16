/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <lcosta-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:22:05 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/07/22 18:57:56 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	in_word;
	int	words;

	in_word = 0;
	words = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			words++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (words);
}

static int	get_word_len(char const	*s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	*extract_word(char const **s, char c)
{
	char	*word;
	int		word_len;

	while (**s == c)
		(*s)++;
	word_len = get_word_len(*s, c);
	word = malloc(word_len + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, *s, word_len);
	word[word_len] = '\0';
	*s += word_len;
	return (word);
}

static char	**handle_empty_string(void)
{
	char	**result;

	result = malloc(1 * sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		i;

	if (!s || !*s)
		return (handle_empty_string());
	word_count = count_words(s, c);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		result[i] = extract_word(&s, c);
		if (!result[i])
		{
			while (--i >= 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
