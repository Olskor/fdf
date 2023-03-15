/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:42 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/15 18:36:25 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <math.h>

# ifndef HEIGHT
#  define HEIGHT 1080
# endif
# ifndef WIDTH
#  define WIDTH 1920
# endif

typedef struct s_Vector3
{
	float	x;
	float	y;
	float	z;
}		t_Vector3;

typedef struct s_triangle
{
	t_Vector3	pos1;
	t_Vector3	pos2;
	t_Vector3	pos3;
}		t_tri;

typedef struct s_mat4
{
	float	m[4][4];
}		t_mat4;

typedef struct s_Int2
{
	int	x;
	int	y;
}		t_Int2;

typedef struct s_Col
{
	float	x;
	float	y;
	float	z;
}		t_Col;

typedef struct s_map
{
	int	sizex;
	int	sizey;
	int	**mappos;
	int	**mapcol;
}		t_map;

typedef struct s_data	t_data;
struct s_data
{
	void	*mlx;
	void	*win;
	t_Int2	g_mpos;
	int		g_mzoom;
	t_map	map;
	int		wi;
	int		he;
	float	far;
	float	near;
	float	fov;
	float	theta;
	t_Int2	(*f)();
};

t_Vector3	vector3(float x, float y, float z);
int			get_sign(int i);
t_Int2		int2(float x, float y);
t_map		get_map(char *file);
int			checkline(t_data *data, t_Int2 pos1, t_Int2 pos2);
t_Int2		iso_proj(t_Vector3 obj, t_data *data);
t_mat4		initmat4(int val);
t_Int2		con_proj(t_Vector3 obj, t_data *data);
void		dataset(t_data *data, char *txt);

#endif