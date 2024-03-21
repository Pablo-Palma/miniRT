/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:18:50 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/21 23:45:39 by math             ###   ########.fr       */
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
}					t_ray;

#endif
