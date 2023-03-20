/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:08:52 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/20 20:45:05 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"
#include "libft.h"

int	dataset(t_data *data, char *txt)
{
	if (!get_map(txt, 0, 0, &data->map))
		return (0);
	data->g_mpos.x = 0;
	data->g_mpos.y = 0;
	data->g_mzoom = 10;
	data->fov = 90.0f;
	data->near = 0.1f;
	data->far = 1000.0f;
	data->zrot = 0.0f;
	data->xrot = 0.0f;
	data->yrot = 0.0f;
	data->f = &iso_proj;
	mlx_mouse_hide(data->mlx, data->win);
	mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
	return (1);
}

int	ft_counti(char *src)
{
	int		i;
	char	**text;

	i = 0;
	text = ft_split(src, ' ');
	while (text[i])
	{
		free(text[i]);
		i++;
	}
	free(text);
	return (i);
}

t_map	*map_color(t_map *map, char *file, int i)
{
	char	*txt;
	char	**val;
	int		obj;
	int		j;

	map->mapcol = malloc(sizeof(int *) * map->sizey);
	obj = open(file, O_RDONLY);
	while (i < map->sizey)
	{
		map->mapcol[i] = malloc(sizeof(int) * map->sizex);
		txt = get_next_line(obj);
		j = 0;
		val = ft_split(txt, ' ');
		free(txt);
		while (j < map->sizex)
		{
			map->mapcol[i][j] = atoibaseskip(val[j]);
			free(val[j++]);
		}
		free(val);
		i++;
	}
	close(obj);
	return (map);
}

t_map	*map_create(t_map *map, char *file, int i)
{
	char	*txt;
	char	**val;
	int		obj;
	int		j;

	map->mappos = malloc(sizeof(int *) * map->sizey);
	obj = open(file, O_RDONLY);
	while (i < map->sizey)
	{
		map->mappos[i] = malloc(sizeof(int) * map->sizex);
		txt = get_next_line(obj);
		j = 0;
		val = ft_split(txt, ' ');
		free(txt);
		while (j < map->sizex)
		{
			map->mappos[i][j] = ft_atoi(val[j]);
			free(val[j++]);
		}
		free(val);
		i++;
	}
	close(obj);
	return (map_color(map, file, 0));
}

int	get_map(char *file, int x, int y, t_map *map)
{
	int		obj;
	char	*txt;

	obj = open(file, O_RDONLY);
	if (obj == -1)
		return (0);
	txt = get_next_line(obj);
	x = ft_counti(txt);
	y = 0;
	while (txt)
	{
		free(txt);
		txt = get_next_line(obj);
		if (txt)
			if (ft_counti(txt) != x)
				return (0);
		y++;
	}
	free(txt);
	close(obj);
	map->sizex = x;
	map->sizey = y;
	map = map_create(map, file, 0);
	return (1);
}
