/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:23:38 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/20 15:36:07 by jauffret         ###   ########.fr       */
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
	if (x > y)
		return (x);
	return (y);
}

t_Vector3	rotz(t_Vector3 i, float theta)
{
	t_mat4		rotmat;

	rotmat = initmat4(0);
	rotmat.m[0][0] = cos(theta);
	rotmat.m[1][0] = -sin(theta);
	rotmat.m[0][1] = sin(theta);
	rotmat.m[1][1] = cos(theta);
	rotmat.m[2][2] = 1;
	rotmat.m[3][3] = 1;
	return (matrixmul(i, rotmat));
}

t_Vector3	rotx(t_Vector3 i, float theta)
{
	t_mat4		rotmat;

	rotmat = initmat4(0);
	rotmat.m[0][0] = 1;
	rotmat.m[1][1] = cos(theta);
	rotmat.m[2][1] = -sin(theta);
	rotmat.m[1][2] = sin(theta);
	rotmat.m[2][2] = cos(theta);
	rotmat.m[3][3] = 1;
	return (matrixmul(i, rotmat));
}

t_Vector3	roty(t_Vector3 i, float theta)
{
	t_mat4		rotmat;

	rotmat = initmat4(0);
	rotmat.m[0][0] = cos(theta);
	rotmat.m[1][1] = 1;
	rotmat.m[2][0] = sin(theta);
	rotmat.m[0][2] = -sin(theta);
	rotmat.m[2][2] = cos(theta);
	rotmat.m[3][3] = 1;
	return (matrixmul(i, rotmat));
}
