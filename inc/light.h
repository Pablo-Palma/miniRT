/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:18:50 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/12 15:12:14 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIGHT_H
# define LIGHT_H

typedef struct	s_light
{
	char 	id[2];	//	'L'
	t_vec3	pos;
	double	brigthness;
}				t_light;

typedef struct	s_ambient_light
{
	char 	id[2];	//	'A'
	double	intensity;
	int		color;
}				t_ambient_light;

#endif
