/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_constructors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:17:56 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/17 16:06:34 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	**nsplit(char *line, char delim, int expected)
{
	char	**parts;
	int		count;

	parts = ft_split(line, delim);
	count = 0;
	while (parts && parts[count])
		count++;
	if (count != expected)
	{
		ft_putstr_fd("miniRT: Incorrect number of parameters: ", 2);
		ft_putstr_fd(line, 2);
		ft_free_arrays(parts);
		return (NULL);
	}
	return (parts);
}

static void	dbfree(char **str)
{
	int i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])	
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

static void	dbfree_two(char **str1, char **str2)
{
	dbfree(str1);
	dbfree(str2);
}

static void	dbfree_three(char **str1, char **str2, char **str3)
{
	dbfree(str1);
	dbfree(str2);
	dbfree(str3);
}

static void	dbfree_four(char **str1, char **str2, char **str3, char **str4)
{
	dbfree(str1);
	dbfree(str2);
	dbfree(str3);
	dbfree(str4);
}

static void	onfail_clean(char *line, void *self)
{
	ft_putstr_fd("on line: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
	if (self)
		free(self);
	self = NULL;
}

void	a_light(void *parent)
{
	t_ambient_light	*self;
	char			**str;
	char			**str_color;

	self = (t_ambient_light *)malloc(sizeof(t_ambient_light));
	str = nsplit(((t_obj *)parent)->line, ' ', 3);
	str_color = nsplit(str[2], ',', 3);
	if (self && str && str_color)
	{
		self->intensity = ft_atof(str[1]);
		self->color = ((ft_atoi(str_color[0]) << 16)
			| (ft_atoi(str_color[1]) << 8)
			| (ft_atoi(str_color[2])));
		((t_obj *)parent)->child = self;
		*((t_obj *)parent)->color = self->color;
	}
	else
		onfail_clean(((t_obj *)parent)->line, self);
	dbfree_two(str, str_color);
}

void	camera(void *parent)
{
	t_cam	*self;
	char	**str;
	char	**str_cordinates;
	char	**str_orientation;

	self = (t_cam *)malloc(sizeof(t_cam));
	((t_obj *)parent)->child = self;
	str = nsplit(((t_obj *)parent)->line, ' ', 4);
	str_cordinates = nsplit(str[1], ',', 3);
	str_orientation = nsplit(str[2], ',', 3);
	if (self && str && str_cordinates && str_orientation)
	{
		self->view_point = (t_vec3){ft_atof(str_cordinates[0]),
									ft_atof(str_cordinates[1]),
									ft_atof(str_cordinates[2])};
		self->orientation = (t_vec3){ft_atof(str_orientation[0]),
									ft_atof(str_orientation[1]),
									ft_atof(str_orientation[2])};
		self->fov = ft_atoi(str[3]);
		*((t_obj *)parent)->origin = &self->view_point;
	}
	dbfree_three(str, str_cordinates, str_orientation);
}

void	light(void *parent)
{
	t_light		*self;
	char		**str;
	char		**str_cordinates;
	char		**str_color;

	self = (t_light *)malloc(sizeof(t_light));
	((t_obj *)parent)->child = self;
	str = nsplit(((t_obj *)parent)->line, ' ', 4);
	str_cordinates = nsplit(str[1], ',', 3);
	str_color = nsplit(str[3], ',', 3);
	if (self && str && str_cordinates && str_color)
	{
		self->pos = (t_vec3){ft_atof(str_cordinates[0]),
							ft_atof(str_cordinates[1]),
							ft_atof(str_cordinates[2])};
		self->brigthness = ft_atof(str[2]);
		self->color = ((ft_atoi(str_color[0]) << 16)
					| (ft_atoi(str_color[1]) << 8)
					| (ft_atoi(str_color[2])));
		*((t_obj *)parent)->origin = &self->pos;
		*((t_obj *)parent)->color = self->color;
	}
	dbfree_three(str, str_cordinates, str_color);
}

void	sphere(void *parent)
{
	t_sphere	*self;
	char		**str;
	char		**str_cordinates;
	char		**str_color;

	self = (t_sphere *)malloc(sizeof(t_sphere));
	((t_obj *)parent)->child = self;
	str = nsplit(((t_obj *)parent)->line, ' ', 4);
	str_cordinates = nsplit(str[1], ',', 3);
	str_color = nsplit(str[3], ',', 3);
	if (self && str && str_cordinates && str_color)
	{
		self->center = (t_vec3){ft_atof(str_cordinates[0]),
								ft_atof(str_cordinates[1]),
								ft_atof(str_cordinates[2])};
		self->radius = ft_atof(str[2]) / 2;
		self->color = ((ft_atoi(str_color[0]) << 16)
					| (ft_atoi(str_color[1]) << 8)
					| (ft_atoi(str_color[2])));
		*((t_obj *)parent)->origin = &self->center;
		*((t_obj *)parent)->color = self->color;
	}
	dbfree_three(str, str_cordinates, str_color);
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
	str = nsplit(((t_obj *)parent)->line, ' ', 4);
	str_point = nsplit(str[1], ',', 3);
	str_normalized = nsplit(str[2], ',', 3);
	str_color = nsplit(str[3], ',', 3);
	if (self && str && str_point && str_normalized && str_color)
	{
		self->point = (t_vec3){ft_atof(str_point[0]),
								ft_atof(str_point[1]),
								ft_atof(str_point[2])};
		self->normal = (t_vec3){ft_atof(str_normalized[0]),
								ft_atof(str_normalized[1]),
								ft_atof(str_normalized[2])};
		self->color = ((ft_atoi(str_color[0]) << 16)
					| (ft_atoi(str_color[1]) << 8)
					| (ft_atoi(str_color[2])));
		*((t_obj *)parent)->origin = &self->point;
		*((t_obj *)parent)->color = self->color;
	}
	dbfree_four(str, str_point, str_normalized, str_color);
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
	str = nsplit(((t_obj *)parent)->line, ' ', 6);
	str_center = nsplit(str[1], ',', 3);
	str_dir = nsplit(str[2], ',', 3);
	str_color = nsplit(str[5], ',', 3);
	if (self && str && str_center && str_dir && str_color)
	{
		self->center = (t_vec3){ft_atof(str_center[0]),
								ft_atof(str_center[1]),
								ft_atof(str_center[2])};
		self->dir = (t_vec3){ft_atof(str_dir[0]),
							ft_atof(str_dir[1]),
							ft_atof(str_dir[2])};
		self->radius = ft_atof(str[3]) / 2;
		self->h = ft_atof(str[4]);
		self->color = ((ft_atoi(str_color[0]) << 16)
					| (ft_atoi(str_color[1]) << 8)
					| (ft_atoi(str_color[2])));
		*((t_obj *)parent)->origin = &self->center;
		*((t_obj *)parent)->color = self->color;
	}
	dbfree_four(str, str_center, str_dir, str_color);
}
