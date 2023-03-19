/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:31:34 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/19 20:52:06 by olskor           ###   ########.fr       */
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

t_Int2	iso_proj(t_Vector3 obj, t_data *data)
{
	t_Int2	pos;
	t_mat4	rotmat;

	obj.x += (float)data->map.sizey / 2;
	obj.y -= (float)data->map.sizex / 2;
	rotmat = initmat4(0);
	rotmat.m[0][0] = cos(data->theta);
	rotmat.m[1][0] = -sin(data->theta);
	rotmat.m[0][1] = sin(data->theta);
	rotmat.m[1][1] = cos(data->theta);
	rotmat.m[2][2] = 1;
	rotmat.m[3][3] = 1;
	obj = matrixmul(obj, rotmat);
	obj.x += data->g_mpos.x + data->g_mpos.y;
	obj.y += data->g_mpos.y - data->g_mpos.x;
	pos.x = (data->wi / 2) + data->g_mzoom * (obj.y - obj.x) / sqrt(2);
	pos.y = (data->he / 2) - data->g_mzoom
		* (obj.y + 2 * obj.z + obj.x) / sqrt(6);
	return (pos);
}

t_Vector3	transform(t_Vector3 i, t_data *data)
{
	t_Vector3	o;
	t_mat4		rotmat;

	i.x += ((float)data->map.sizey / 2);
	i.y -= ((float)data->map.sizex / 2);
	rotmat = initmat4(0);
	rotmat.m[0][0] = cos(data->theta);
	rotmat.m[1][0] = -sin(data->theta);
	rotmat.m[0][1] = sin(data->theta);
	rotmat.m[1][1] = cos(data->theta);
	rotmat.m[2][2] = 1;
	rotmat.m[3][3] = 1;
	i = matrixmul(i, rotmat);
	o.x = i.x + data->g_mpos.x;
	o.y = i.z + data->g_mpos.y;
	o.z = -i.y - (float)max(data->map.sizex, data->map.sizey);
	return (o);
}

t_Int2	con_proj(t_Vector3 obj, t_data *data)
{
	float		ffovrad;
	t_mat4		matproj;
	t_Int2		projected;

	obj = transform(obj, data);
	ffovrad = 1.0f / tanf(data->fov * 0.5f / 180.0f * 3.14159f);
	matproj = initmat4(0);
	matproj.m[0][0] = ((float)data->he / (float)data->wi) * ffovrad;
	matproj.m[1][1] = ffovrad;
	matproj.m[2][2] = data->far / (data->far - data->near);
	matproj.m[3][2] = (-data->far * data->near) / (data->far - data->near);
	matproj.m[2][3] = 1.0f;
	matproj.m[3][3] = 0.0f;
	obj = matrixmul(obj, matproj);
	obj.x += 1.0f;
	obj.y += 1.0f;
	projected.x = obj.x * 0.5f * (float)data->wi;
	projected.y = obj.y * 0.5f * (float)data->he;
	if (obj.z <= 1.0f)
		projected = int2(0, 0);
	return (projected);
}
