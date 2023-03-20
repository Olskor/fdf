/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:07:13 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/20 14:41:07 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_data *data)
{
	int	i;

	mlx_destroy_image(data->mlx, data->img.mlx_img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	i = 0;
	while (i < data->map.sizey)
	{
		free(data->map.mappos[i]);
		free(data->map.mapcol[i]);
		i++;
	}
	free(data->mlx);
	free(data->map.mappos);
	free(data->map.mapcol);
	exit(0);
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
	dataset(&data, argv[1]);
	data.img.mlx_img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx, &loop, &data);
	mlx_hook(data.win, 4, 1L << 2, &mouse_handle, &data);
	mlx_hook(data.win, 2, 1L << 0, &handle_input, &data);
	mlx_hook(data.win, 17, 1L << 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
