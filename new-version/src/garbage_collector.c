/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:35:23 by alouriga          #+#    #+#             */
/*   Updated: 2025/03/24 09:24:30 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_lstadd_back8(t_node **lst, t_node *new)
{
	t_node	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	*globalizer_head(int mode, void *ptr)
{
	static t_node	*rl_lst;

	if (mode == 1)
	{
		rl_lst = ptr;
		return (NULL);
	}
	else
		return (rl_lst);
}

int	store_smart_mallocs(void *ptr_to_add)
{
	t_node	*head;
	t_node	*new_node;

	head = globalizer_head(0, NULL);
	new_node = ft_lstnew8(ptr_to_add);
	if (!new_node)
	{
		exit(1);
	}
	if (!head)
		globalizer_head(1, new_node);
	else
		ft_lstadd_back8(&head, new_node);
	return (1);
}

void	*smart_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr && store_smart_mallocs(ptr))
		return (ptr);
	else
	{
		smart_free();
		exit(1);
	}
}

void	smart_free(void)
{
	t_node	*current;
	t_node	*next;

	current = globalizer_head(0, NULL);
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	globalizer_head(1, NULL);
}
