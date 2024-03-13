/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:18:50 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/13 18:35:51 by mamagalh@st      ###   ########.fr       */
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
