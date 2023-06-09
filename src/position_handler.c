/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:36:45 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/20 16:27:42 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
