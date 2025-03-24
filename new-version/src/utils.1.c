/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:46:33 by alouriga          #+#    #+#             */
/*   Updated: 2025/03/24 09:22:59 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_node	*ft_lstnew8(void *ptr_to_store)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		exit (1);
	new_node->ptr = ptr_to_store;
	new_node->next = NULL;
	return (new_node);
}

void	ft_error_2(const char *str, int fd)
{
	close(fd);
	smart_free();
	printf("Error\n");
	printf("%s", str);
	exit(1);
}

int	len_cal(t_list *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		if (ft_strlen(list->str) > i)
			i = ft_strlen(list->str);
		list = list->next;
	}
	return (i);
}

char	**list_to_array(t_list *list)
{
	t_list	*lst;
	char	**map;
	int		i;
	int		len;

	i = 0;
	len = len_cal(list);
	lst = list;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	map = smart_malloc((i + 1) * sizeof(char *));
	i = 0;
	while (list)
	{
		map[i] = ft_strdup1(list->str, len);
		i++;
		list = list->next;
	}
	map[i] = NULL;
	i = 0;
	return (map);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
