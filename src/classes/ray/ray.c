/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 06:28:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/30 13:36:26 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	ray_generic(t_vec3 origin, t_vec3 direction)
{
	t_ray ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

void	*ray_new(void *ray)
{
	t_ray *self;

	self = (t_ray *)malloc(sizeof(t_ray));
	if (!self)
		return (NULL);
	self->obj = (t_obj **)malloc(sizeof(t_obj *));
	self->next = (t_list **)malloc(sizeof(t_list *));
	self->origin = ((t_ray *)ray)->origin;
	self->direction = ((t_ray *)ray)->direction;
	self->t = INFINITY;
	*self->obj = NULL;
	*self->next = NULL;
	return ((void *)self);
}

void	ray_clean(void *node)
{
	t_ray *self;

	self = (t_ray *)((t_list *)node)->content;
	self->origin = (t_vec3){0,0,0};
	self->direction = (t_vec3){0,0,0};
	self->t = INFINITY;
	*(self->obj) = NULL;
	*self->next = NULL;
}

// {
// 	((t_ray *)self)->origin = (t_vec3){0,0,0};
// 	((t_ray *)self)->direction = (t_vec3){0,0,0};
// 	((t_ray *)self)->t = INFINITY;
// 	*(((t_ray *)self)->obj) = NULL;
// 	*((t_ray *)self)->next = NULL;
// }

void	ray_cpy(void *self, void *ray)
{
	((t_ray *)self)->origin = ((t_ray *)ray)->origin;
	((t_ray *)self)->direction = ((t_ray *)ray)->direction;
}

void	ray_delete(void *param)
{
	t_ray	*self;

	if (!param)
		return;
	self = (t_ray *)param;
	if (self->next)
		ft_lstclear(self->next, ray_delete);
	free(self->obj);
	free(self->next);
	free(self);
}

void	ray_mv_to_pool(t_list **poll, t_list **ray_list)
{
	if (*((t_ray *)((*ray_list)->content))->next)
	{
		ray_mv_to_pool(poll, ((t_ray *)((*ray_list)->content))->next);
		*((t_ray *)((*ray_list)->content))->next = NULL;
	}
	lst_mv_all_to_pool(poll, ray_list, ray_clean);
}

void	ray_print(t_ray *ray)
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

void	ray_print_list(t_list *ray, int level)
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
		ray_print((t_ray *)(ray->content));
		if (((t_ray *)(ray->content))->next)
			ray_print_list(*((t_ray *)(ray->content))->next, level);
		ray = ray->next;
	}
}

void	ray_trace_light(t_ray *ray, t_list *obj_list, t_list **pool)
{
	t_light	*light;
	t_ray	temp;

	if (!(ray && ray->obj))
		return ;
	while (!is_child(obj_list->content, "L"))
		obj_list = obj_list->next;
	light = ((t_obj *)obj_list->content)->child;
	temp.origin = vector_add(ray->origin, vector_scale(ray->direction, ray->t));
	while (light)
	{
		temp.direction = vector_sub(light->pos, temp.origin);
		ft_lstadd_back(ray->next, lst_getpool_node(pool, ray_new, ray_cpy, &temp));
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
//
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
// 		ft_lstadd_back(&(ray->next), ft_lstnew(ray_new(origin, direction)));
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
	//t_vec3	view_dir;
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
			//view_dir = normalize(ray->direction); //obs: this was negated
			light_dir = normalize(next_ray->direction); //obs: this was negated
			pxl->diffuse = calculate_diffuse(light_dir, norm, ((t_light *)((*ray->obj)->child))->brigthness);
			//pxl->specular = calculate_specular(view_dir, light_dir, norm, 1.0, 100.0);
		}
		else
		{
			pxl->diffuse = 0.0;
			pxl->specular = 0.0;
		}
		float	ambient = ambient_light.intensity;
		int		base_color = *(*ray->obj)->color;
		int r = (base_color >> 16) & 0xFF;
		int g = (base_color >> 8) & 0xFF;
		int b = base_color & 0xFF;
		r = fmin(255, (r * ambient) + (r * pxl->diffuse) + (255 * pxl->specular) + ((pxl->color >> 16) & 0xFF));
		g = fmin(255, (g * ambient) + (g * pxl->diffuse) + (255 * pxl->specular) + ((pxl->color >> 8) & 0xFF));
		b = fmin(255, (b * ambient) + (b * pxl->diffuse) + (255 * pxl->specular) + ((pxl->color) & 0xFF));
		// pxl->color = mix_colors(ambient_light, *(*ray->obj)->color, pxl->diffuse, pxl->specular);
		pxl->color = (r << 16) | (g << 8) | b;
		ray_list = ray_list->next;
	}
}

