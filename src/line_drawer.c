/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:11:13 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/20 20:39:42 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	abs_max(int x, int y)
{
	if (abs(x) > abs(y))
		return (abs(x));
	return (abs(y));
}

int	checkline(t_Int2 pos1, t_Int2 pos2)
{
	if (pos1.x > WIDTH || pos1.y > HEIGHT)
		if (pos2.x > WIDTH || pos2.y > HEIGHT)
			return (1);
	if (pos1.x < 0 || pos1.y < 0)
		if (pos2.x < 0 || pos2.y < 0)
			return (1);
	return (0);
}

int	color(int pos, int len, t_Int2 col)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	increment[0] = (double)((get_r(col.y)) - (get_r(col.x))) / (double)len;
	increment[1] = (double)((get_g(col.y)) - (get_g(col.x))) / (double)len;
	increment[2] = (double)((get_b(col.y)) - (get_b(col.x))) / (double)len;
	new[0] = (get_r(col.x)) + pos * increment[0];
	new[1] = (get_g(col.x)) + pos * increment[1];
	new[2] = (get_b(col.x)) + pos * increment[2];
	newcolor = create_trgb(0, new[0], new[1], new[2]);
	return (newcolor);
}

void	lined(t_Int2 pos1, t_Int2 pos2, t_Int2 col, t_data *data)
{
	t_Int2	dpos;
	int		len;
	t_Int2	pos;

	dpos = int2(pos2.x - pos1.x, pos2.y - pos1.y);
	len = abs_max(dpos.x, dpos.y);
	if (abs(dpos.x) > abs(dpos.y))
	{
		pos.x = pos1.x;
		while (pos.x != pos2.x)
		{
			pos.y = pos1.y + dpos.y * (pos.x - pos1.x) / dpos.x;
			img_pix_put(&data->img, pos.x, pos.y, color
				(abs_max(pos.x - pos1.x, pos.y - pos1.y), len, col));
			pos.x += get_sign(dpos.x);
		}
	}
	pos.y = pos1.y;
	while (pos.y != pos2.y)
	{
		pos.x = pos1.x + dpos.x * (pos.y - pos1.y) / dpos.y;
		img_pix_put(&data->img, pos.x, pos.y, color
			(abs_max(pos.x - pos1.x, pos.y - pos1.y), len, col));
		pos.y += get_sign(dpos.y);
	}
}

void	draw_line(t_data *data, t_Int2 pos1, t_Int2 pos2)
{
	t_Int2	proj1;
	t_Int2	proj2;
	t_Int2	col;

	proj1 = data->f(vector3(-pos1.y, pos1.x, data->map.mappos[pos1.y][pos1.x]),
			data);
	proj2 = data->f(vector3(-pos2.y, pos2.x, data->map.mappos[pos2.y][pos2.x]),
			data);
	col.x = data->map.mapcol[pos1.y][pos1.x];
	col.y = data->map.mapcol[pos2.y][pos2.x];
	if (checkline(proj1, proj2))
		return ;
	lined(proj1, proj2, col, data);
}
