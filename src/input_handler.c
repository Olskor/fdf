/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:18:17 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/20 13:22:50 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_handle(int button, int x, int y, t_data *data)
{
	if (button == 4)
	{
		data->g_mzoom *= 2;
		data->fov -= 2.0f;
		printf("%d", button);
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
	return (input_next(keysym, data));
}
