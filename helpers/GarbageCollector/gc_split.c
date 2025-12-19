/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abouknan          #+#    #+#             */
/*   Updated: 2025/12/19 00:00:00 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	*get_word(char const *s, char c, size_t *index)
{
	size_t	start;
	size_t	len;
	char	*word;

	while (s[*index] && s[*index] == c)
		(*index)++;
	start = *index;
	len = 0;
	while (s[*index] && s[*index] != c)
	{
		len++;
		(*index)++;
	}
	word = (char *)gc_malloc(len + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, &s[start], len);
	word[len] = '\0';
	return (word);
}

char	**gc_split(char const *s, char c)
{
	char	**result;
	size_t	word_count;
	size_t	i;
	size_t	index;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)gc_malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	index = 0;
	while (i < word_count)
	{
		result[i] = get_word(s, c, &index);
		if (!result[i])
			return (NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}
