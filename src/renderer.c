/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 01:13:30 by olskor            #+#    #+#             */
/*   Updated: 2023/03/20 20:39:54 by olskor           ###   ########.fr       */
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

int	render(t_data *data)
{
	t_Int2	p;

	p = int2(0, render_background(&data->img, 0));
	while (p.y < data->map.sizey - 1)
	{
		while (p.x < data->map.sizex - 1)
		{
			draw_line(data, int2(p.x, p.y), int2(p.x, p.y + 1));
			draw_line(data, int2(p.x, p.y), int2(p.x + 1, p.y));
			if (p.x >= data->map.sizex - 2)
				draw_line(data, int2(p.x + 1, p.y), int2(p.x + 1, p.y + 1));
			if (p.y >= data->map.sizey - 2)
				draw_line(data, int2(p.x, p.y + 1), int2(p.x + 1, p.y + 1));
			p.x++;
		}
		p.x = 0 * p.y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	return (0);
}
