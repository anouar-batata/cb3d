/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:37:56 by bzinedda          #+#    #+#             */
/*   Updated: 2025/03/24 10:38:18 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			converted_c;

	if (!s)
		return (NULL);
	converted_c = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == converted_c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == converted_c)
		return ((char *) &s[i]);
	return (NULL);
}
