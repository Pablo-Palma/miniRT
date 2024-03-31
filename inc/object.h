/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:18:50 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/31 17:33:47 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	OBJECT_H
# define OBJECT_H

typedef struct s_sphere
{
	char	identifier[3];	// 'sp'
	t_vec3	center;
	double	radius;
	int		color;
	double	diameter;
	double	reflective;
}				t_sphere;

typedef struct s_cyl
{
	char	id[2];	//	'cl'
	t_vec3	center;
	t_vec3	dir;
	double	radius;
	double	h;
	int		color;
	double	reflective;

}			t_cyl;

typedef struct s_plane
{
	char 	id[2];	//	'pl'
	t_vec3	point;
	t_vec3	normal;
	int		color;
	double	reflective;
}			t_plane;

typedef struct s_circle
{
	char 	id[2];	//	'ci'
	t_vec3	center;
	t_vec3	normal;
	double	radius;
	int		color;
	double	reflective;
}			t_circle;

typedef struct s_obj
{
	char	*line;
	void	*child;
	t_vec3	**origin;
	int		*color;
}			t_obj;

typedef struct	s_ray
{
    t_vec3			origin;
    t_vec3			direction;
    double			t;
	t_obj			**obj;
	t_list			**next;
	ssize_t			reflect_level;
	bool			img_trace;
}					t_ray;

#endif
