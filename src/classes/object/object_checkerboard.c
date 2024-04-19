/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_checkerboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:50:41 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/19 11:38:21 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	checkerboard_pl(t_vec3 point)
{
	double	scale;
	int		x;
	int		y;
	int		z;

	scale = 0.5;
	x = abs((int)floor(point.x * scale)) % 2;
	y = abs((int)floor(point.y * scale)) % 2;
	z = abs((int)floor(point.z * scale)) % 2;
	if ((x ^ y ^ z) == 0)
		return (WHITE);
	else
		return (BLACK);
}

static void	get_uv_sp(double *u, double *v, t_vec3 p)
{
	double	phi;
	double	theta;

	phi = atan2(p.z, p.x);
	theta = asin(p.y);
	*u = 1 - (phi + M_PI) / (2 * M_PI);
	*v = (theta + M_PI / 2) / M_PI;
}

int	checkerboard_sp(t_sphere sphere, t_vec3 point)
{
	int		x;
	int		y;
	double	u;
	double	v;

	get_uv_sp(&u, &v, normalize(vector_sub(point, sphere.center)));
	x = (int)(floor(u * (double)10.0)) % 2;
	y = (int)(floor(v * (double)10.0)) % 2;
	if (x == y)
		return (WHITE);
	else
		return (BLACK);
}

static void	get_uv_cyl(double *u, double *v, t_cyl cyl, t_vec3 point)
{
	t_vec3	temp_vec;
	double	proj_length;
	double	height;

	temp_vec = vector_sub(point, cyl.center);
	if (cyl.caps != 0)
	{
		*u = (temp_vec.x / cyl.radius + 1) / 2;
		*v = (temp_vec.y / cyl.radius + 1) / 2;
		return ;
	}
	proj_length = vector_dot_product(temp_vec, cyl.dir);
	temp_vec = vector_sub(temp_vec, vector_scale(cyl.dir, proj_length));
	*u = (atan2(temp_vec.y, temp_vec.x) + M_PI) / (2 * M_PI);
	*u = fmod(*u, 1.0);
	height = proj_length + (cyl.h / 2.0);
	*v = height / cyl.h;
	*v = fmod(*v, 1.0);
}

int	checkerboard_cyl(t_cyl cyl, t_vec3 point)
{
	int		x;
	int		y;
	double	u;
	double	v;

	get_uv_cyl(&u, &v, cyl, point);
	x = (int)(floor(u * ((2 * M_PI * cyl.radius) / (cyl.radius / 2)))) % 2;
	y = (int)(floor(v * (cyl.h / (cyl.radius / 2)))) % 2;
	if (x == y)
		return (WHITE);
	else
		return (BLACK);
}
