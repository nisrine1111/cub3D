/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:30:13 by abouknan          #+#    #+#             */
/*   Updated: 2025/11/29 20:30:14 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "../libft/libft.h"
# include <stdlib.h>

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}					t_gc;

void			ft_exit(int status);
void			*ft_malloc(size_t size);
void			*gc_malloc(size_t size);
void			gc_free_all(void);
t_gc			*gc_new_node(void *ptr);
void			free_node_content(void *content);
void			*gc_calloc(size_t count, size_t size);
char			*gc_strdup(const char *s);
char			*gc_strjoin(char const *s1, char const *s2);
char			**gc_split(char const *s, char c);
char			*gc_strtrim(char const *s1, char const *set);

#endif
