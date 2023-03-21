/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:23:38 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/21 04:42:45 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_Vector3	matrixmul(t_Vector3 i, t_mat4 m)
{
	t_Vector3	o;
	float		w;

	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
	if (w != 0.0f)
	{
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}
	return (o);
}

int	max(int x, int y)
{
	if (x >= y)
		return (x);
	return (y);
}

t_Vector3	rota(t_Vector3 i, float z, float y, float x)
{
	t_mat4		rotmat;

	rotmat = initmat4(0);
	rotmat.m[0][0] = cos(y) * cos(z);
	rotmat.m[1][0] = sin(x) * sin(y) * cos(z) - cos(x) * sin(z);
	rotmat.m[2][0] = cos(x) * sin(y) * cos(z) + sin(x) * sin(z);
	rotmat.m[0][1] = cos(y) * sin(z);
	rotmat.m[1][1] = sin(x) * sin(y) * sin(z) + cos(x) * cos(z);
	rotmat.m[2][1] = cos(x) * sin(y) * sin(z) - sin(x) * cos(z);
	rotmat.m[0][2] = -sin(y);
	rotmat.m[1][2] = sin(x) * cos(y);
	rotmat.m[2][2] = cos(x) * cos(y);
	rotmat.m[3][3] = 1;
	return (matrixmul(i, rotmat));
}
