/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:18:17 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/24 15:10:01 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hook_setup(t_data *data)
{
	mlx_loop_hook(data->mlx, &loop, data);
	mlx_hook(data->win, 4, 1L << 2, &mouse_handle, data);
	mlx_hook(data->win, 2, 1L << 0, &handle_input, data);
	mlx_hook(data->win, 17, 1L << 0, &close_window, data);
}

int	mouse_handle(int button, int x, int y, t_data *data)
{
	if (button == 4)
	{
		data->g_mzoom *= 2;
		data->fov -= 2.0f;
	}
	if (button == 5)
	{
		data->g_mzoom /= 2;
		data->fov += 2.0f;
	}
	if (button == 1)
	{
		data->g_mpos.x += (data->mouspos.x - WIDTH / 2) / 2;
		data->g_mpos.y += (data->mouspos.y - HEIGHT / 2) / 2;
	}
	x = y;
	y = x;
	if (data->g_mzoom <= 0)
		data->g_mzoom = 1;
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
	if (keysym == XK_a)
		data->yrot += 0.1f;
	if (keysym == XK_d)
		data->yrot -= 0.1f;
	if (keysym == XK_r)
	{
		if (data->rotate)
			data->rotate = 0;
		else
			data->rotate = 1;
	}
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
	if (keysym == XK_q)
		data->zrot += 0.1f;
	if (keysym == XK_e)
		data->zrot -= 0.1f;
	if (keysym == XK_w)
		data->xrot += 0.1f;
	if (keysym == XK_s)
		data->xrot -= 0.1f;
	return (input_next(keysym, data));
}
