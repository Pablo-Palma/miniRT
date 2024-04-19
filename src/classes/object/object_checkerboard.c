/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_checkerboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:50:41 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/19 10:19:44 by pabpalma         ###   ########.fr       */
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

int	checkerboard_cyl(t_cyl cyl, t_vec3 point)
{
	int		x;
	int		y;
	double	u;
	double	v;

	if (cyl.caps == 1)
		get_uv_cap(&u, &v, cyl, point);
	else
		get_uv_cyl(&u, &v, cyl, point);
	x = (int)(floor(u * ((2 * M_PI * cyl.radius) / (cyl.radius / 2)))) % 2;
	y = (int)(floor(v * (cyl.h / (cyl.radius / 2)))) % 2;
	if (x == y)
		return (WHITE);
	else
		return (BLACK);
}
