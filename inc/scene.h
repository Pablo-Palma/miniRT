/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:18:50 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/19 21:45:09 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SCENE_H
# define SCENE_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_cam
{
	char	identifier[2];	//	'C'
	t_vec3	view_point;
	t_vec3	orientation;
	int		fov; //Field of view(campo de vision).
}	t_cam;

#endif
