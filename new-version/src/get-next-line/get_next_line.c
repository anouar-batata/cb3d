/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:54:25 by bzinedda          #+#    #+#             */
/*   Updated: 2025/03/22 00:42:56 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<< HEAD
#include "libft.h"
=======
>>>>>>> 87eaaafcb41192bac92b031bfea14394231652e4
#include "cub3d.h"

static char	*ft_readfrombuffer(int fd, char *rest)
{
	char	*buffer;
	int		n_bytes;

	buffer = smart_malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	while (!(ft_strchr(rest, '\n')))
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes == 0)
			break ;
		if (n_bytes < 0)
		{
			break ;
		}
		buffer[n_bytes] = '\0';
		rest = ft_strjoin(rest, buffer);
	}
	return (rest);
}

static char	*ft_pickup_line(char *rest)
{
	char	*line;
	char	*from_nl;
	int		rest_len;
	int		afternl_len;
	int		line_len;

	if (!rest)
		return (NULL);
	from_nl = ft_strchr(rest, '\n');
	rest_len = ft_strlen(rest);
	if (from_nl == NULL)
		from_nl = "";
	afternl_len = ft_strlen(from_nl) - 1;
	if (afternl_len == -1)
		afternl_len = 0;
	line_len = rest_len - afternl_len;
	line = smart_malloc(line_len + 1);
	line[line_len] = 0;
	while (--line_len >= 0)
		*(line + line_len) = *(rest + line_len);
	return (line);
}

static char	*ft_pickup_rest(char *rest)
{
	char	*from_nl;
	char	*str;
	int		afternl_len;

	from_nl = ft_strchr(rest, '\n');
	if (from_nl == NULL)
		from_nl = "";
	afternl_len = ft_strlen(from_nl) - 1;
	if (afternl_len == -1)
		afternl_len = 0;
	str = smart_malloc(afternl_len + 1);
	str[afternl_len] = 0;
	if (afternl_len)
		++from_nl;
	while (afternl_len--)
		*(str + afternl_len) = *(from_nl + afternl_len);
	if (str[0] == 0)
	{
		return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	rest = ft_readfrombuffer(fd, rest);
	line = ft_pickup_line(rest);
	if (!line)
		return (ft_free(&rest));
	rest = ft_pickup_rest(rest);
	return (line);
}
