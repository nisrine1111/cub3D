/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:18:53 by abouknan          #+#    #+#             */
/*   Updated: 2024/12/20 23:27:28 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "../GarbageCollector/malloc.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*gnl_substr(char const *s, unsigned int start, size_t len);
size_t	gnl_strlen(const char *str);
char	*gnl_strchr(const char *s, int i);
char	*gnl_strdup(const char *s);
char	*gnl_strjoin(char *s1, char const *s2);
char	*get_next_line(int fd);

#endif
