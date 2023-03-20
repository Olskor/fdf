/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:42 by jauffret          #+#    #+#             */
/*   Updated: 2023/03/20 18:41:02 by jauffret         ###   ########.fr       */
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
	float	w;
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

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_cam
{
	float		near;
	float		far;
	float		fov;
	t_Vector3	pos;
	t_Vector3	rot;
}	t_cam;

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
	float	zrot;
	float	yrot;
	float	xrot;
	t_Int2	mouspos;
	t_img	img;
	t_Int2	(*f)();
};

t_Vector3	vector3(float x, float y, float z);
int			get_sign(int i);
t_Int2		int2(float x, float y);
int			get_map(char *file, int x, int y, t_map *map);
t_Int2		iso_proj(t_Vector3 obj, t_data *data);
t_mat4		initmat4(int val);
t_Int2		con_proj(t_Vector3 obj, t_data *data);
int			dataset(t_data *data, char *txt);
void		img_pix_put(t_img *img, int x, int y, int color);
int			render(t_data *data);
int			atoibaseskip(char *nbr);
int			loop(t_data *data);
int			mouse_handle(int button, int x, int y, t_data *data);
int			input_next(int keysym, t_data *data);
int			handle_input(int keysym, t_data *data);
int			close_window(t_data *data);
t_Vector3	matrixmul(t_Vector3 i, t_mat4 m);
int			max(int x, int y);
t_Vector3	rotz(t_Vector3 i, float theta);
t_Vector3	rotx(t_Vector3 i, float theta);
t_Vector3	roty(t_Vector3 i, float theta);
void		draw_line(t_data *data, t_Int2 pos1, t_Int2 pos2);
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
void		hook_setup(t_data *data);

#endif