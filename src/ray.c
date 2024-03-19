/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 06:28:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/19 03:01:50 by math             ###   ########.fr       */
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
	self->direction = (normalize(direction));
	self->obj = (t_list **)malloc(sizeof(t_list *));
	*(self->obj) = NULL;
	self->t = 10000000;
	self->next = NULL;
	return (self);
}

void	delete_ray(void *param)
{
	t_ray	*self;

	if (!param)
		return;
	self = (t_ray *)param;
	if (self->next)
		ft_lstclear(&self->next, delete_ray);
	free(self->obj);
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
			ray->origin.x *ray->t,
			ray->origin.y  *ray->t,
			ray->origin.z * ray->t);
		print_obj(((t_obj *)(*ray->obj)->content));
	}
	else
	{
		printf("\tDirection: (%.2f, %.2f, %.2f)\n",
			ray->origin.x,
			ray->origin.y,
			ray->origin.z);
		printf("\tObject: (null))\n");
	}
	if (ray->next)
		print_ray((t_ray *)ray->next->content);
}

void	ray_trace_light(t_ray *ray)
{
	t_vec3	origin;
	t_vec3	direction;
	t_list	*light;

	if (!(ray && *ray->obj))
		return ;
	light = objchr(*ray->obj, "L");
	while (light)
	{
		origin = vector_add(ray->origin, vector_scale(ray->direction, ray->t));
		direction = vector_sub(origin, ((t_light *)((t_obj *)light->content)->child)->pos);
		ft_lstadd_back(&(ray->next), ft_lstnew(new_ray(origin, direction)));
		*((t_ray *)ft_lstlast(ray->next)->content)->obj = light;
		((t_ray *)ft_lstlast(ray->next)->content)->t = vector_length(direction);
		light = light->next;
		light = objchr(light, "L");
	}
}

// void	ray_draw(t_ray *ray, t_pixel *pix, t_ambient_light ambient_light)
// {
// 	t_list	*obj;
// 	t_light	*light;
// 	t_vec3	view_dir;
// 	t_vec3	light_dir;


// 	obj = (t_list *)(*(ray->obj));
// 	if (!obj)
// 		return;
// 	light = ((t_light *)((t_list *)*(((t_ray *)(ray->next->content))->obj)));

// 	t_vec3	point = vector_add(ray->origin, vector_scale(ray->direction, ray->t));
// 	t_vec3	norm = get_normal(obj, point);
// 	light_dir = normalize(vector_sub(light->pos, point));
// 	view_dir = normalize(vector_negate(ray->direction));
// 	pix->diffuse += calculate_diffuse(light_dir, norm, light->brigthness);
// 	pix->specular += calculate_specular(view_dir, light_dir, norm, 0.1, 100000.0);

// 	pix->color = mix_colors(ambient_light, CIAN, pix->diffuse, pix->specular);
// }

void	ray_draw(t_ray *ray, t_pixel *pix, t_ambient_light ambient_light)
{
	t_light	*light = ((t_light *)((t_obj *)objchr(*ray->obj, "L")->content)->child);
	
	t_vec3	view_dir;
	t_vec3	light_dir;

	t_vec3	point = ((t_ray *)ray->next->content)->origin;
	t_vec3	norm = get_normal((t_list *)(*(ray->obj)), point);
	light_dir = normalize(vector_negate(((t_ray *)ray->next->content)->direction));
	view_dir = normalize(vector_negate(ray->direction));
	pix->diffuse = calculate_diffuse(light_dir, norm, light->brigthness);
	pix->specular = calculate_specular(view_dir, light_dir, norm, 0.1, 100000.0);

	pix->color = mix_colors(ambient_light, CIAN, pix->diffuse, pix->specular);
}

