/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:18:50 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/05 16:51:14 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	STRUCT_H
# define STRUCT_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_sphere
{
	t_vec3	center;
	double	radius;
	int		color;
}				t_sphere;

typedef struct	s_light
{
	t_vec3	pos;
	double	brigthness;
}				t_light;

typedef struct	s_cam
{
	t_vec3	view_point;
	t_vec3	orientation;
	double	fov; //Field of view(campo de vision).
}	t_cam;

#endif
