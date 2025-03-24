/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:37:45 by bzinedda          #+#    #+#             */
/*   Updated: 2025/03/24 10:38:23 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*str;
	unsigned char	converted_c;

	i = 0;
	str = b;
	converted_c = (unsigned char) c;
	while (i < len)
	{
		str[i] = converted_c;
		i++;
	}
	return (str);
}
