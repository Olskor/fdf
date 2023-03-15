/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:07:13 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/15 18:08:17 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_data *data, t_Int2 pos1, t_Int2 pos2, int color)
{
	t_Int2	dpos;
	t_Int2	pos;

	dpos.x = pos2.x - pos1.x;
	dpos.y = pos2.y - pos1.y;
	if (checkline(data, pos1, pos2))
		return ;
	if (abs(dpos.x) > abs(dpos.y))
	{
		pos.x = pos1.x;
		while (pos.x != pos2.x)
		{
			pos.y = pos1.y + dpos.y * (pos.x - pos1.x) / dpos.x;
			mlx_pixel_put(data->mlx, data->win, pos.x, pos.y, color);
			pos.x += get_sign(dpos.x);
		}
		return ;
	}
	pos.y = pos1.y;
	while (pos.y != pos2.y)
	{
		pos.x = pos1.x + dpos.x * (pos.y - pos1.y) / dpos.y;
		mlx_pixel_put(data->mlx, data->win, pos.x, pos.y, color);
		pos.y += get_sign(dpos.y);
	}
}

int	render(t_data *data)
{
	t_Int2	p;
	int		height1;
	int		height2;

	if (data->win != NULL)
	{
		p = int2(0, 0);
		while (p.y < data->map.sizey - 1)
		{
			while (p.x < data->map.sizex - 1)
			{
				height1 = data->map.mappos[p.y][p.x];
				height2 = data->map.mappos[p.y + 1][p.x];
				draw_line(data, data->f(vector3(-p.y, p.x, height1), data),
					data->f(vector3(-(p.y + 1), p.x, height2), data), 16777215);
				height2 = data->map.mappos[p.y][p.x + 1];
				draw_line(data, data->f(vector3(-p.y, p.x, height1), data),
					data->f(vector3(-p.y, p.x + 1, height2), data), 16777215);
				p.x++;
			}
			p.x = 0 * p.y++;
		}
	}
	return (0);
}

int	input_next(int keysym, t_data *data)
{
	if (keysym == XK_Page_Up)
		data->fov -= 2.0f;
	if (keysym == XK_Page_Down)
		data->fov += 2.0f;
	if (keysym == XK_c)
		data->f = con_proj;
	if (keysym == XK_i)
		data->f = iso_proj;
	mlx_clear_window(data->mlx, data->win);
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		return (0);
	}
	if (keysym == XK_Left)
		data->g_mpos.x -= 1;
	if (keysym == XK_Right)
		data->g_mpos.x += 1;
	if (keysym == XK_Up)
		data->g_mpos.y -= 1;
	if (keysym == XK_Down)
		data->g_mpos.y += 1;
	if (keysym == XK_Page_Up)
		data->g_mzoom *= 2;
	if (keysym == XK_Page_Down)
		data->g_mzoom /= 2;
	if (keysym == XK_a)
		data->theta += 0.1f;
	if (keysym == XK_d)
		data->theta -= 0.1f;
	if (data->g_mzoom <= 0)
		data->g_mzoom = 1;
	return (input_next(keysym, data));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc <= 1)
		return (1);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.wi = WI;
	data.he = HE;
	data.win = mlx_new_window(data.mlx, data.wi, data.he, "fdf");
	if (!data.win)
	{
		free(data.win);
		return (1);
	}
	data.f = iso_proj;
	dataset(&data, argv[1]);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_key_hook(data.win, &handle_input, &data);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	return (0);
}
