/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:26:24 by ccommiss          #+#    #+#             */
/*   Updated: 2021/06/29 11:40:41 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dispatch(t_fdf *env, int pt1, int pt2)
{
	initall(env, pt1, pt2);
	drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x,
		color(env, pt1, pt2));
	if (fabsf(env->pt.dx) > fabs(env->pt.dy))
		bresen1(env, pt1, pt2);
	else
		bresen2(env, pt1, pt2);
}

int	sendpoints(t_fdf *env)
{
	int	pt;
	int	i;

	pt = 0;
	i = 0;
	while (pt < env->size - 1)
	{
		if (i++ < env->x_width - 1)
			dispatch(env, pt, pt + 1);
		else
			i = 0;
		if (pt < env->size - env->x_width)
			dispatch(env, pt, (pt + env->x_width));
		pt++;
	}
	return (1);
}

int	redisplay(t_fdf *env)
{
	erase(env);
	sendpoints(env);
	base(env);
	return (1);
}

int	main(int ac, char **argv)
{
	int		fd;
	t_fdf	env;
	char	*file;

	file = NULL;
	if (ac != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	init_struct(&env);
	if (!(ft_analyse(&file, fd, &env)))
		ft_error(&env);
	sendpoints(&env);
	mlx_put_image_to_window(env.mlx_ptr, env.win_ptr, env.img_ptr, 0, 0);
	mlx_hook(env.win_ptr, 9, 1L << 21, redisplay, &env);
	mlx_hook(env.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		closewin, &env);
	mlx_hook(env.win_ptr, KEY_PRESS, KEY_PRESS_MASK, keyrepartition, &env);
	base(&env);
	mlx_loop(env.mlx_ptr);
	return (0);
}
