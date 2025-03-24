/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:37:51 by bzinedda          #+#    #+#             */
/*   Updated: 2025/03/24 12:00:18 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	count_words(char const *s, char c)
{
	size_t	counter;
	size_t	is_counter_triggred;

	counter = 0;
	is_counter_triggred = 0;
	while (*s != '\0')
	{
		if (*s != c && (is_counter_triggred == 0))
		{
			is_counter_triggred = 1;
			counter++;
		}
		else if (*s == c)
			is_counter_triggred = 0;
		s++;
	}
	return (counter);
}

static	void	fill_word(char *currentWord, char const *s,
							size_t s_index, size_t word_size)
{
	int	i;

	i = 0;
	while (word_size > 0)
	{
		currentWord[i] = s[s_index - word_size];
		i++;
		word_size--;
	}
	currentWord[i] = '\0';
}

static	char	**allocate_strings(char const *s, char delimeter,
									size_t nbw, char **splited_strings)
{
	size_t	s_index;
	size_t	cure_i;
	size_t	word_size;

	cure_i = 0;
	word_size = 0;
	s_index = 0;
	while (cure_i < nbw)
	{
		while (s[s_index] && s[s_index] == delimeter)
			s_index++;
		while (s[s_index] && s[s_index] != delimeter)
		{
			word_size++;
			s_index++;
		}
		splited_strings[cure_i] = (char *)smart_malloc(word_size + 1);
		fill_word(splited_strings[cure_i], s, s_index, word_size);
		word_size = 0;
		cure_i++;
	}
	splited_strings[cure_i] = NULL;
	return (splited_strings);
}

char	**ft_split(char const *s, char c)
{
	char	**splited_strings;
	size_t	nbw;

	if (!s)
		return (NULL);
	nbw = count_words(s, c);
	splited_strings = (char **)smart_malloc(sizeof(char *) * (nbw + 1));
	splited_strings = allocate_strings(s, c, nbw, splited_strings);
	return (splited_strings);
}
