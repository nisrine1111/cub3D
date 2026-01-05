/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:30:11 by abouknan          #+#    #+#             */
/*   Updated: 2026/01/05 20:26:13 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_gc	**get_head(void)
{
	static t_gc	*head;

	return (&head);
}

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

void	*ft_malloc(size_t size)
{
	t_gc		*new_node;
	void		*ptr;
	t_gc		**head;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = gc_new_node(ptr);
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	head = get_head();
	if (!*head)
		*head = new_node;
	else
	{
		new_node->next = *head;
		*head = new_node;
	}
	return (ptr);
}

void	gc_free_all(void)
{
	t_gc		*current;
	t_gc		*next;
	t_gc		**head;

	head = get_head();
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	*head = NULL;
}
