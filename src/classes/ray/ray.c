/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 06:28:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/17 12:39:19 by mamagalh@st      ###   ########.fr       */
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
	self->reflect_level = 0;
	self->img_trace = 0;
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
	self->reflect_level = 0;
	self->img_trace = 0;
}

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

void	ray_mv_to_pool(t_list **pool, t_list **ray_list)
{
	t_list	*cur;

	cur = *ray_list;
	while (cur)
	{
		if (*((t_ray *)(cur->content))->next)
		{
			ray_mv_to_pool(pool, ((t_ray *)(cur->content))->next);
			*((t_ray *)(cur->content))->next = NULL;
		}
		cur = cur->next;
	}
	lst_mv_all_to_pool(pool, ray_list, ray_clean);
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

void	ray_trace_img(t_ray *ray, t_list **pool)
{
	t_ray	temp;

	if (!(ray && ray->obj))
		return ;
	if (ray->reflect_level >= MAX_REFLECT_LEVEL)
		return ;
	temp.origin = vector_add(ray->origin, vector_scale(ray->direction, ray->t));
	temp.direction = vector_reflect(ray->direction , get_normal(*ray->obj, temp.origin));
	ft_lstadd_back(ray->next, lst_getpool_node(pool, ray_new, ray_cpy, &temp));
	((t_ray *)ft_lstlast(*ray->next)->content)->reflect_level += 1;
	((t_ray *)ft_lstlast(*ray->next)->content)->img_trace = 1;
}

t_vec3	ray_sum(t_ray *ray, t_vec3 alight)
{
	t_list	*ray_list;
	t_ray	*next_ray;
	t_vec3	pxl_light;
	t_vec3	temp;
	t_vec3	view_dir;
	t_vec3	light_dir;
	t_vec3	norm;
	double	diffuse;
	double	specular;
	
	pxl_light = (t_vec3){0,0,0};
	ray_list = *ray->next;
	while (ray_list)
	{
		next_ray = ray_list->content;
		if (!*next_ray->obj)
			return (pxl_light);
		if (is_child(*next_ray->obj, "L"))
		{
			temp = color_to_vec(*(*next_ray->obj)->color);
			norm = normalize(get_normal(*ray->obj, next_ray->origin));
			view_dir = normalize(ray->direction);
			light_dir = normalize(next_ray->direction);
			diffuse = calculate_diffuse(light_dir, norm, ((t_light *)(*next_ray->obj)->child)->brigthness);
			temp = vector_scale(temp, diffuse);
			temp = vector_fmax(temp, alight);
			temp = vector_multiply(temp, normalize(color_to_vec(*(*ray->obj)->color)));
			specular = calculate_specular(view_dir, light_dir, norm, 1.0, 100.0);
			temp = vector_add(temp, vector_scale(color_to_vec(*(*next_ray->obj)->color), specular));
			pxl_light = vector_add(pxl_light, temp);
		}
		else if (next_ray->img_trace)
		{
			/*handle reflection*/
			temp = ray_sum(next_ray, alight);
			temp = vector_fmax(temp, alight);
			temp = vector_multiply(temp, normalize(color_to_vec(*(*ray->obj)->color)));
			pxl_light = temp;
			//pxl_light = vector_add(pxl_light, temp);
		}
		// else
		// {
		// 	//temp = color_to_vec(BLACK);
		// 	//temp = vector_fmax(temp, alight);
		// 	//temp = vector_multiply(temp, normalize(color_to_vec(*(*ray->obj)->color)));
		// 	//pxl_light = temp;
		// }
		ray_list = ray_list->next;
	}
	if (vector_cmp(pxl_light, color_to_vec(BLACK)))
	{
		pxl_light = vector_multiply(alight, normalize(color_to_vec(*(*ray->obj)->color)));
		// pxl_light = vector_fmax(pxl_light, alight);
		// pxl_light = alight;
	}
	return (pxl_light);
}

