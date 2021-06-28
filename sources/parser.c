/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 18:31:04 by ccommiss          #+#    #+#             */
/*   Updated: 2021/06/28 14:07:33 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	freetab(void ***tab)
{
	int	x;

	x = 0;
	while ((*tab)[x])
	{
		free((*tab)[x]);
		x++;
	}
	free(*tab);
	*tab = NULL;
}

int	ft_fuckingnorme(t_fdf *data, int x, int y, int pt)
{
	data->coord[pt] = (float *)malloc(sizeof(float) * 3);
	if (!data->coord[pt])
		ft_error(data);
	data->coord[pt][0] = (float)x - 0.5 * data->x_width;
	data->coord[pt][1] = (float)y - 0.5 * data->y_height;
	return (1);
}

int	ft_coord(t_fdf *data, char **tab, int pt, char **line)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	data->altmax = 0;
	while (tab[y])
	{
		line = ft_strsplit(tab[y], ' ');
		while (line[x])
		{
			ft_fuckingnorme(data, x, y, pt);
			data->coord[pt][2] = (float)ft_atoi(line[x]);
			if (data->coord[pt][2] > data->altmax)
				data->altmax = data->coord[pt][2];
			x++;
			pt++;
		}
		freetab((void ***)&line);
		x = 0;
		y++;
	}
	freetab((void ***)&tab);
	data->coord[pt] = 0;
	return (1);
}

int	mallocdata(t_fdf *data, char **file)
{
	char	**tab;
	char	**line;
	int		pt;

	pt = 0;
	line = NULL;
	tab = ft_strsplit(*file, '\n');
	if (!tab)
	{
		freetab((void ***)&tab);
		ft_error(data);
		return (0);
	}
	data->size = data->x_width * data->y_height;
	data->zoom = data->x_width / data->y_height * 3;
	data->alt = 0.1;
	data->coord = (float **)malloc(sizeof(float *) * (data->size + 1));
	if (!data->coord)
		ft_error(data);
	if (!(ft_coord(data, tab, pt, line)))
		ft_error(data);
	free(*file);
	return (1);
}

int	ft_analyse(char **file, int fd, t_fdf *data)
{
	int		a;
	char	*line;
	char	**tab;

	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		a = 0;
		tab = ft_strsplit(line, ' ');
		while (tab[a])
			a++;
		if (data->x_width == 0)
			data->x_width = a;
		freetab((void ***)&tab);
		if (a != data->x_width || data->x_width <= 1)
			ft_error(data);
		data->y_height++;
		line = ft_strjoin2(line, "\n");
		*file = ft_strjoin2(*file, line);
		free(line);
	}
	if (get_next_line(fd, &line) == -1 || data->y_height <= 1)
		ft_error(data);
	mallocdata(data, file);
	return (1);
}
