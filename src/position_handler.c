/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:36:45 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/15 14:28:48 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	checkline(t_data *data, t_Int2 pos1, t_Int2 pos2)
{
	if (pos1.x > data->wi || pos1.y > data->he)
		if (pos2.x > data->wi || pos2.y > data->he)
			return (1);
	if (pos1.x < 0 || pos1.y < 0)
		if (pos2.x < 0 || pos2.y < 0)
			return (1);
	return (0);
}

int	get_sign(int i)
{
	if (i >= 0)
		return (1);
	return (-1);
}

t_mat4	initmat4(int val)
{
	t_mat4	matrix;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			matrix.m[i][j] = val;
			j++;
		}
		i++;
	}
	return (matrix);
}

t_Vector3	vector3(float x, float y, float z)
{
	t_Vector3	pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
	return (pos);
}

t_Int2	int2(float x, float y)
{
	t_Int2	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}
