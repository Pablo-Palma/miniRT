/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:01:35 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/13 18:35:02 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include <stdio.h>

static void	print_a_light(void *obj)
{
	t_ambient_light	*ambient_light;

	ambient_light = (t_ambient_light *)obj;
	printf("Ambient Light:\n");
	printf("\tRatio: %.2f\n", ambient_light->intensity);
	printf("\tColor: (%d, %d, %d)\n",
			(ambient_light->color >> 16) & 0xFF,
			(ambient_light->color >> 8) & 0xFF,
			ambient_light->color & 0xFF);
}

static void	print_camera(void *obj)
{
	t_cam	*camera;

	camera = (t_cam *)obj;
	printf("Camera:\n");
	printf("\tView Point: (%.2f, %.2f, %.2f)\n",
			camera->view_point.x,
			camera->view_point.y,
			camera->view_point.z);
	printf("\tOrientation: (%.2f, %.2f, %.2f)\n",
			camera->orientation.x,
			camera->orientation.y,
			camera->orientation.z);
	printf("\tFOV: %d\n", camera->fov);
}

static void	print_light(void *obj)
{
	t_light	*light;

	light = (t_light *)obj;
	printf("Light:\n");
	printf("\tPosition: (%.2f, %.2f, %.2f)\n",
			light->pos.x,
			light->pos.y,
			light->pos.z);
	printf("\tBrightness: %.2f\n", light->brigthness);
}

static void	print_sphere(void *obj)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)obj;
	printf("Sphere:\n");
	printf("\tCenter: (%.2f, %.2f, %.2f)\n",
			sphere->center.x,
			sphere->center.y,
			sphere->center.z);
	printf("\tRadius: %.2f\n", sphere->radius);
	printf("\tColor: (%d, %d, %d)\n",
			(sphere->color >> 16) & 0xFF,
			(sphere->color >> 8) & 0xFF,
			sphere->color & 0xFF);
}

static void	print_plane(void *obj)
{
	t_plane	*plane;

	plane = (t_plane *)obj;
	printf("Plane:\n");
	printf("\tPoint: (%.2f, %.2f, %.2f)\n",
			plane->point.x,
			plane->point.y,
			plane->point.z);
	printf("\tNormal: (%.2f, %.2f, %.2f)\n",
			plane->normal.x,
			plane->normal.y,
			plane->normal.z);
	printf("\tColor: (%d, %d, %d)\n",
			(plane->color >> 16) & 0xFF,
			(plane->color >> 8) & 0xFF,
			plane->color & 0xFF);
}

static void	print_cylinder(void *obj)
{
	t_cyl	*cylinder;

	cylinder = (t_cyl *)obj;
	printf("Cylinder:\n");
	printf("\tCenter: (%.2f, %.2f, %.2f)\n",
			cylinder->center.x,
			cylinder->center.y,
			cylinder->center.z);
	printf("\tDirection: (%.2f, %.2f, %.2f)\n",
			cylinder->dir.x,
			cylinder->dir.y,
			cylinder->dir.z);
	printf("\tRadius: %.2f\n", cylinder->radius);
	printf("\tHeight: %.2f\n", cylinder->h);
	printf("\tColor: (%d, %d, %d)\n",
			(cylinder->color >> 16) & 0xFF,
			(cylinder->color >> 8) & 0xFF,
			cylinder->color & 0xFF);
}

void	print_obj(void *self)
{
	if (!ft_strncmp(((t_obj *)self)->line, "A", 1)) //ambient light
		print_a_light(((t_obj *)self)->child);
	else if (!ft_strncmp(((t_obj *)self)->line, "C", 1)) //camera
		print_camera(((t_obj *)self)->child);
	else if (!ft_strncmp(((t_obj *)self)->line, "L", 1)) //light
		print_light(((t_obj *)self)->child);
	else if (!ft_strncmp(((t_obj *)self)->line, "sp", 2)) //sphere
		print_sphere(((t_obj *)self)->child);
	else if (!ft_strncmp(((t_obj *)self)->line, "pl", 2)) //plane
		print_plane(((t_obj *)self)->child);
	else if (!ft_strncmp(((t_obj *)self)->line, "cy", 2)) //cylinder
		print_cylinder(((t_obj *)self)->child);
}
