/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 06:28:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/25 19:53:50 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_ray	*new_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray *self;

	self = (t_ray *)malloc(sizeof(t_ray));
	if (!self)
		return (NULL);
	self->origin = origin;
	self->direction = direction;
	self->t = 10000000;
	self->obj = (t_obj **)malloc(sizeof(t_obj *));
	*self->obj = NULL;
	self->next = (t_list **)malloc(sizeof(t_list *));
	*self->next = NULL;
	return (self);
}

void	delete_ray(void *param)
{
	t_ray	*self;

	if (!param)
		return;
	self = (t_ray *)param;
	if (self->next)
		ft_lstclear(self->next, delete_ray);
	free(self->obj);
	free(self->next);
	free(self);
}

void	print_ray(t_ray *ray)
{
	printf("Ray:\n");
	printf("\tOrigin: (%.2f, %.2f, %.2f)\n",
			ray->origin.x,
			ray->origin.y,
			ray->origin.z);
	if (*ray->obj)
	{
		printf("\tDirection: (%.2f, %.2f, %.2f)\n",
			ray->direction.x,
			ray->direction.y,
			ray->direction.z);
		printf("\tIntersection: (%.2f, %.2f, %.2f)\n",
			ray->direction.x *ray->t,
			ray->direction.y  *ray->t,
			ray->direction.z * ray->t);
		print_obj(ray->obj);
	}
	else
	{
		printf("\tDirection: (%.2f, %.2f, %.2f)\n",
			ray->direction.x,
			ray->direction.y,
			ray->direction.z);
		printf("\tObject: (null))\n");
	}
}

void	print_ray_list(t_list *ray, int level)
{
	++level;
	printf("=====<level%d>=====\n", level);
	if (!ray)
		printf("(null)\n");
	while (ray)
	{
		if (!ray->content)
		{
			printf("(null)\n");
			return ;
		}
		print_ray((t_ray *)(ray->content));
		if (((t_ray *)(ray->content))->next)
			print_ray_list(*((t_ray *)(ray->content))->next, level);
		ray = ray->next;
	}
}


void	ray_trace_light(t_ray *ray, t_list *obj_list)
{
	t_vec3	origin;
	t_vec3	direction;
	t_light	*light;

	if (!(ray && ray->obj))
		return ;
	while (!is_child(obj_list->content, "L"))
		obj_list = obj_list->next;
	light = ((t_obj *)obj_list->content)->child;
	origin = vector_add(ray->origin, vector_scale(ray->direction, ray->t));
	while (light)
	{
		direction = vector_sub(light->pos, origin);
		ft_lstadd_back(ray->next, ft_lstnew(new_ray(origin, direction)));
		obj_list = obj_list->next;
		if (is_child(obj_list->content, "L"))
			light = ((t_obj *)obj_list->content)->child;
		else
			light = NULL;
	}
}
// {
// 	t_vec3	origin;
// 	t_vec3	direction;
// 	t_light	*light;

// 	if (!(ray && *ray->obj))
// 		return ;
// 	obj_list = objchr(obj_list, "L");
// 	if (!ft_strncmp(((t_obj *)(obj_list->content))->line, "L", 1))
// 		light = (t_light *)((t_obj *)(obj_list->content))->child;
// 	else
// 		light = NULL;
// 	origin = vector_add(ray->origin, vector_scale(ray->direction, ray->t));
// 	while (light)
// 	{
// 		direction = vector_sub(light->pos, origin);
// 		ft_lstadd_back(&(ray->next), ft_lstnew(new_ray(origin, direction)));
// 		obj_list = obj_list->next;
// 		if (!ft_strncmp(((t_obj *)(obj_list->content))->line, "L", 1))
// 			light = (t_light *)((t_obj *)(obj_list->content))->child;
// 		else
// 			light = NULL;
// 	}
// }

void	ray_sum(t_ray *ray, t_pixel *pxl, t_ambient_light ambient_light)
{
	t_list	*ray_list;
	t_ray	*next_ray;
	t_vec3	view_dir;
	t_vec3	light_dir;
	
	ray_list = *ray->next;
	while (ray_list)
	{
		next_ray = ray_list->content;
		if (!*next_ray->obj)
			return ;
		if (is_child(*next_ray->obj, "L"))
		{
			t_vec3	norm = get_normal(*ray->obj, next_ray->origin);
			view_dir = normalize((ray->direction)); //obs: this was negated
			light_dir = normalize((next_ray->direction)); //obs: this was negated
			pxl->diffuse = fmax(pxl->diffuse, calculate_diffuse(light_dir, norm, ((t_light *)((*ray->obj)->child))->brigthness));
			pxl->specular = fmax(pxl->specular ,calculate_specular(view_dir, light_dir, norm, 1.0, 100.0));
		}
		else
		{
			pxl->diffuse = 0.0;
			pxl->specular = 0.0;
		}
		pxl->color = mix_colors(ambient_light, *(*ray->obj)->color, pxl->diffuse, pxl->specular);
		ray_list = ray_list->next;
	}
}

