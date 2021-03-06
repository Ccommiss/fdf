/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pratic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 16:06:18 by ccommiss          #+#    #+#             */
/*   Updated: 2021/06/29 11:41:32 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	base(t_fdf *env)
{
	int	h;

	h = env->screen_h * 0.1;
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h, BLU, "Moves :");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h + 20, WHITE,
		" <- / UP / DOWN / ->");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h + 40, BLU, "Zoom");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h + 60, WHITE, " + / - ");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h + 80, BLU,
		"Projections (iso/para):");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h + 100, WHITE, "I - P");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h + 120, BLU, "Rotation :");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h + 140, WHITE, "4 6 8");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h + 160, BLU, "Altitude :");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h + 180, WHITE, "H / L");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h + 200, BLU, "Reset view");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h + 220, WHITE, "    0");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h * 10 - 100, RED, "Close");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, h * 10 - 70, WHITE, "Esc");
}

void	erase(t_fdf *env)
{
	int	*pixels;
	int	x;
	int	y;

	pixels = (int *)env->info;
	x = 0;
	y = 0;
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	while (y * env->screen_w + x < env->screen_w * env->screen_h)
	{
		pixels[(y * env->screen_w + x)] = 000000;
		x++;
	}
}

void	reinit(t_fdf *env)
{
	env->trans_y = 0;
	env->trans_x = 0;
	env->rot_X = 0.52;
	env->rot_Y = 0.52;
	env->rot_Z = 0;
	env->zoom = env->screen_w / env->screen_h * 5;
	env->alt = env->zoom + 0.1;
	erase(env);
	sendpoints(env);
	base(env);
}

void	init_struct(t_fdf *env)
{
	env->mlx_ptr = mlx_init();
	mlx_get_screen_size(env->mlx_ptr, &env->screen_w, &env->screen_h);
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->screen_w,
			env->screen_h, "fdf");
	env->img_ptr = mlx_new_image(env->mlx_ptr, env->screen_w, env->screen_h);
	env->info = mlx_get_data_addr(env->img_ptr, &env->bpp,
			&env->sl, &env->endian);
	env->zoom = env->screen_w / env->screen_h * 5;
	env->rot_X = 0.52;
	env->rot_Z = 0;
	env->rot_Y = 0.52;
	env->trans_x = 0;
	env->trans_y = 0;
	env->pt.dx = 0;
	env->pt.dy = 0;
	env->view.iso = 1;
	env->view.para = 0;
	env->loop = 0;
	env->x_width = 0;
	env->y_height = 0;
	env->size = 0;
	env->alt = env->zoom + 0.1;
	env->coord = 0;
}

int	ft_error(t_fdf *env)
{
	int	x;

	x = 0;
	if (env->img_ptr != NULL)
		mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	if (env->win_ptr != NULL)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	if (env->coord != NULL)
		freetab((void ***)&env->coord);
	ft_putstr("An error occured. Please try with a valid map. \n");
	exit(0);
}
