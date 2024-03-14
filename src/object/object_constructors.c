/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_constructors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:17:56 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/13 18:30:33 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static void	dbfree(char **str)
{
	int i;

	i = -1;
	while (str[++i])	
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

void	a_light(void *parent)
{
	t_ambient_light	*self;
	char			**str;
	char			**str_color;

	self = malloc(sizeof(t_ambient_light));
	((t_obj *)parent)->child = self;
	str = ft_split(((t_obj *)parent)->line, ' ');
	self->intensity = ft_atof(str[1]);
	str_color = ft_split(str[2], ',');
	self->color = ((ft_atoi(str_color[0]) << 16)
				| (ft_atoi(str_color[1]) << 8)
				| (ft_atoi(str_color[2])));
	dbfree(str);
	dbfree(str_color);	
}

void	camera(void *parent)
{
	t_cam	*self;
	char	**str;
	char	**str_cordinates;
	char	**str_normalized;

	self = (t_cam *)malloc(sizeof(t_cam));
	((t_obj *)parent)->child = self;
	str = ft_split(((t_obj *)parent)->line, ' ');
	str_cordinates = ft_split(str[1], ',');
	self->view_point = (t_vec3){ft_atof(str_cordinates[0]),
								ft_atof(str_cordinates[1]),
								ft_atof(str_cordinates[2])};
	str_normalized = ft_split(str[2], ',');
	self->orientation = (t_vec3){ft_atof(str_normalized[0]),
								ft_atof(str_normalized[1]),
								ft_atof(str_normalized[2])};
	self->fov = ft_atoi(str[3]);
	dbfree(str);
	dbfree(str_cordinates);
	dbfree(str_normalized);
}

void	light(void *parent)
{
	t_light		*self;
	char		**str;
	char		**str_cordinates;
	// char		**str_color;  ONLY FOR BONUS PART

	self = (t_light *)malloc(sizeof(t_light));
	((t_obj *)parent)->child = self;
	str = ft_split(((t_obj *)parent)->line, ' ');
	str_cordinates = ft_split(str[1], ',');
	self->pos = (t_vec3){ft_atof(str_cordinates[0]),
						ft_atof(str_cordinates[1]),
						ft_atof(str_cordinates[2])};
	self->brigthness = ft_atof(str[2]);
	// str_color = ft_split(str[3], ',');
	// self->color = ((ft_atoi(str_color[0]) << 16)
	// 			| (ft_atoi(str_color[1]) << 8)
	// 			| (ft_atoi(str_color[2])));
	dbfree(str);
	dbfree(str_cordinates);
	// dbfree(str_color);
}

void	sphere(void *parent)
{
	t_sphere	*self;
	char		**str;
	char		**str_cordinates;
	char		**str_color;

	self = (t_sphere *)malloc(sizeof(t_sphere));
	((t_obj *)parent)->child = self;
	str = ft_split(((t_obj *)parent)->line, ' ');
	str_cordinates = ft_split(str[1], ',');
	self->center = (t_vec3){ft_atof(str_cordinates[0]),
							ft_atof(str_cordinates[1]),
							ft_atof(str_cordinates[2])};
	self->radius = ft_atof(str[2]);
	str_color = ft_split(str[3], ',');
	self->color = ((ft_atoi(str_color[0]) << 16)
				| (ft_atoi(str_color[1]) << 8)
				| (ft_atoi(str_color[2])));
	dbfree(str);
	dbfree(str_cordinates);
	dbfree(str_color);
}

void	plane(void *parent)
{
	t_plane	*self;
	char	**str;
	char	**str_point;
	char	**str_normalized;
	char	**str_color;

	self = (t_plane *)malloc(sizeof(t_plane));
	((t_obj *)parent)->child = self;
	str = ft_split(((t_obj *)parent)->line, ' ');
	str_point = ft_split(str[1], ',');
	self->point = (t_vec3){ft_atof(str_point[0]),
							ft_atof(str_point[1]),
							ft_atof(str_point[2])};
	str_normalized = ft_split(str[2], ',');
	self->normal = (t_vec3){ft_atof(str_normalized[0]),
							ft_atof(str_normalized[1]),
							ft_atof(str_normalized[2])};
	str_color = ft_split(str[3], ',');
	self->color = ((ft_atoi(str_color[0]) << 16)
				| (ft_atoi(str_color[1]) << 8)
				| (ft_atoi(str_color[2])));
	dbfree(str);
	dbfree(str_point);
	dbfree(str_normalized);
	dbfree(str_color);
}

void	cylinder(void *parent)
{
	t_cyl	*self;
	char	**str;
	char	**str_center;
	char	**str_dir;
	char	**str_color;

	self = (t_cyl *)malloc(sizeof(t_cyl));
	((t_obj *)parent)->child = self;
	str = ft_split(((t_obj *)parent)->line, ' ');
	str_center = ft_split(str[1], ',');
	self->center = (t_vec3){ft_atof(str_center[0]),
							ft_atof(str_center[1]),
							ft_atof(str_center[2])};
	str_dir = ft_split(str[2], ',');
	self->dir = (t_vec3){ft_atof(str_dir[0]),
						ft_atof(str_dir[1]),
						ft_atof(str_dir[2])};
	self->radius = ft_atof(str[3]);
	self->h = ft_atof(str[4]);
	str_color = ft_split(str[5], ',');
	self->color = ((ft_atoi(str_color[0]) << 16)
				| (ft_atoi(str_color[1]) << 8)
				| (ft_atoi(str_color[2])));
	dbfree(str);
	dbfree(str_center);
	dbfree(str_dir);
	dbfree(str_color);
}
