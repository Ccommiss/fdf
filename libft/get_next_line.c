/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 10:42:24 by ccommiss          #+#    #+#             */
/*   Updated: 2021/06/29 11:41:10 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_managestock(char **final, char **line)
{
	int		g;
	char	*tmp;

	g = 0;
	while ((*final)[g])
	{
		if ((*final)[g] == '\n')
		{
			*line = ft_strsub(*final, 0, g);
			if ((*final)[g + 1] == '\0')
				ft_memdel((void **)final);
			else
			{
				tmp = *final;
				*final = ft_strdup(*final + g + 1);
				free(tmp);
			}
			return (1);
		}
		g++;
	}
	*line = ft_strdup(*final);
	ft_memdel((void **)final);
	return (1);
}

int	read_line(int *i, int fd, char **stock)
{
	*i = read(fd, stock, BUFF_SIZE);
	return (*i);
}

int	get_next_line(const int fd, char **line)
{
	char			stock[BUFF_SIZE + 1];
	static char		*final = NULL;
	int				i;
	int				a;
	int				k;

	a = 0;
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || read(fd, stock, 0) < 0)
		return (-1);
	i = 0;
	while ((a != 1) && (read_line(&i, fd, (char **)&stock) > 0))
	{
		k = 0;
		stock[i] = '\0';
		final = ft_strjoin2(final, stock);
		while (final[k] && final[k] != '\n')
			k++;
		if (final[k] == '\n')
			a = 1;
	}
	if (i < 0)
		return (-1);
	if (final != NULL)
		return (ft_managestock(&final, line));
	return (0);
}
