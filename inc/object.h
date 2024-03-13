/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:18:50 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/13 18:20:38 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	OBJECT_H
# define OBJECT_H

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

typedef struct s_sphere
{
	char	identifier[3];	// 'sp'
	t_vec3	center;
	double	radius;
	int		color;
	double	diameter;
}				t_sphere;

typedef struct s_cyl
{
	char	id[2];	//	'cl'
	t_vec3	center;
	t_vec3	dir;
	double	radius;
	double	h;
	int		color;

}			t_cyl;

typedef struct s_plane
{
	char 	id[2];	//	'pl'
	t_vec3	point;
	t_vec3	normal;
	int		color;
}			t_plane;

typedef struct s_light
{
	t_vec3	pos;
	double	brigthness;
	// int		color;
}			t_light;

typedef struct s_cam
{
	t_vec3	view_point;
	t_vec3	orientation;
	int		fov; //Field of view(campo de vision).
}			t_cam;

typedef struct s_ambient_light
{
	double	ratio;
	int		color;
}			t_ambient_light;

typedef struct s_obj
{
	char	*line;
	void	*child;
}			t_obj;

#endif
