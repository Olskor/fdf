/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:07:13 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/16 02:58:48 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_data *data)
{
	data->map.sizey = 0;
	mlx_destroy_image(data->mlx, data->img.mlx_img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->map.mappos);
	free(data->map.mapcol);
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
	if (keysym == XK_Escape)
		return (close_window(data));
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
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
	data.wi = WIDTH;
	data.he = HEIGHT;
	data.win = mlx_new_window(data.mlx, data.wi, data.he, "fdf");
	if (!data.win)
	{
		free(data.win);
		return (1);
	}
	data.f = iso_proj;
	dataset(&data, argv[1]);
	data.img.mlx_img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, 2, 1L << 0, &handle_input, &data);
	mlx_hook(data.win, 17, 1L << 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
