/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 01:13:30 by olskor            #+#    #+#             */
/*   Updated: 2023/03/20 13:21:50 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	loop(t_data *data)
{
	render(data);
	mlx_mouse_get_pos(data->mlx, data->win, &data->mouspos.x, &data->mouspos.y);
	mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
	data->g_mpos.x += (data->mouspos.x - WIDTH / 2) / 2;
	data->g_mpos.y += (data->mouspos.y - HEIGHT / 2) / 2;
	if (data->g_mzoom <= 0)
		data->g_mzoom = 1;
	if (data->fov < 1)
		data->fov = 1.0f;
	if (data->fov > 160.0f)
		data->fov = 160.0f;
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x >= WIDTH || y >= HEIGHT)
		return ;
	if (x < 0 || y < 0)
		return ;
	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
	return (0);
}

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
			img_pix_put(&data->img, pos.x, pos.y, color);
			pos.x += get_sign(dpos.x);
		}
		return ;
	}
	pos.y = pos1.y;
	while (pos.y != pos2.y)
	{
		pos.x = pos1.x + dpos.x * (pos.y - pos1.y) / dpos.y;
		img_pix_put(&data->img, pos.x, pos.y, color);
		pos.y += get_sign(dpos.y);
	}
}

int	render(t_data *data)
{
	t_Int2	p;
	int		height1;
	int		height2;

	p = int2(0, render_background(&data->img, 0));
	while (p.y < data->map.sizey - 1)
	{
		while (p.x < data->map.sizex - 1)
		{
			height1 = data->map.mappos[p.y][p.x];
			height2 = data->map.mappos[p.y + 1][p.x];
			draw_line(data, data->f(vector3(-p.y, p.x, height1), data),
				data->f(vector3(-(p.y + 1), p.x, height2), data),
				data->map.mapcol[p.y + 1][p.x]);
			height2 = data->map.mappos[p.y][p.x + 1];
			draw_line(data, data->f(vector3(-p.y, p.x, height1), data),
				data->f(vector3(-p.y, p.x + 1, height2), data),
				data->map.mapcol[p.y][p.x + 1]);
			p.x++;
		}
		p.x = 0 * p.y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	data->theta += 0.01f;
	return (0);
}
