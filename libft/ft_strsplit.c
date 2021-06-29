/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:30:51 by ccommiss          #+#    #+#             */
/*   Updated: 2021/06/29 10:48:05 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countarrays(char const *s, char c)
{
	int	nb_arr;
	int	i;

	nb_arr = 1;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			nb_arr++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nb_arr);
}

char	*ft_mallocline(char *splitted, const char *s, int c)
{
	int	n;

	n = 0;
	while (s[n] && s[n] != c)
		n++;
	if (n != 0)
	{
		splitted = (char *)malloc(n * sizeof(char) + 1);
		if (!splitted)
			return (NULL);
		return (splitted);
	}
	return (NULL);
}

char	**ft_fill(char **splitted, const char *s, int i_max, int c)
{
	int	i;
	int	j;

	i = 0;
	while (*s && i < i_max)
	{
		j = 0;
		splitted[i] = ft_mallocline(splitted[i], s, c);
		while (s[j] && s[j] != c)
		{
			splitted[i][j] = s[j];
			j++;
		}
		if (j != 0)
		{
			splitted[i][j] = '\0';
			i++;
		}
		while (s[j] && s[j] == c)
			j++;
		s = s + j;
	}
	splitted[i] = NULL;
	return (splitted);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**splitted;
	int		i_max;

	if (!s)
		return (NULL);
	i_max = ft_countarrays(s, c);
	splitted = (char **)malloc((i_max + 1) * sizeof(char *));
	if (!splitted)
		return (NULL);
	ft_fill(splitted, s, i_max, c);
	return (splitted);
}
