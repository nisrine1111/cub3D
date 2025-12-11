/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:30:08 by abouknan          #+#    #+#             */
/*   Updated: 2025/11/29 20:30:09 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*gc_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (count == 0 || size == 0)
		return (NULL);
	if (count > (size_t)-1 / size)
		return (NULL);
	total_size = count * size;
	ptr = gc_malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}

char	*gc_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = (char *)gc_malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

char	*gc_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (gc_strdup(s2));
	if (!s2)
		return (gc_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)gc_malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	return (result);
}

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

static int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*gc_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_in_set(s1[end - 1], set))
		end--;
	len = end - start;
	result = (char *)gc_malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, &s1[start], len);
	result[len] = '\0';
	return (result);
}
