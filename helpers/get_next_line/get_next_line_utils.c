/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:30:12 by abouknan          #+#    #+#             */
/*   Updated: 2024/12/20 14:50:38 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strjoin(char *s1, const char *s2)
{
	int		total_len;
	char	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = gnl_strdup("");
	if (!s2)
		return (NULL);
	total_len = gnl_strlen(s1) + gnl_strlen(s2) + 1;
	str = (char *)ft_malloc(total_len * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*gnl_strdup(const char *src)
{
	char	*dest;
	int		i;
	int		len;

	if (!src)
		return (NULL);
	len = gnl_strlen(src);
	dest = (char *)ft_malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == cc)
		return ((char *)s + i);
	return (NULL);
}

char	*gnl_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = gnl_strlen(s);
	if (start >= s_len || len == 0)
		return (gnl_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	str = (char *)ft_malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}