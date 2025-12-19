/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:30:11 by abouknan          #+#    #+#             */
/*   Updated: 2025/11/29 20:30:12 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free_node_content(void *content)
{
	t_gc	*node;

	if (!content)
		return ;
	node = (t_gc *)content;
	if (node->ptr)
		free(node->ptr);
}

t_gc	*gc_new_node(void *ptr)
{
	t_gc	*node;

	node = (t_gc *)malloc(sizeof(t_gc));
	if (!node)
		return (NULL);
	node->ptr = ptr;
	node->next = NULL;
	return (node);
}

void	*gc_malloc(size_t size)
{
	static t_gc	*head;
	t_gc		*new_node;
	void		*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = gc_new_node(ptr);
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	if (!head)
		head = new_node;
	else
	{
		new_node->next = head;
		head = new_node;
	}
	return (ptr);
}

void	gc_free_all(void)
{
	static t_gc	*head;
	t_gc		*current;
	t_gc		*next;

	current = head;
	while (current)
	{
		next = current->next;
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	head = NULL;
}

void	*ft_malloc(size_t size)
{
	return (gc_malloc(size));
}
