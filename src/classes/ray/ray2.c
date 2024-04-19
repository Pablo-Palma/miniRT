/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:01:45 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/19 12:12:13 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
			ray->direction.x * ray->t,
			ray->direction.y * ray->t,
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
		ft_lstadd_back(ray->next, lst_getpool_node(pool, ray_new, ray_cpy,
				&temp));
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
	temp.direction = vector_reflect(ray->direction, get_normal(*ray->obj,
				temp.origin));
	ft_lstadd_back(ray->next, lst_getpool_node(pool, ray_new, ray_cpy, &temp));
	((t_ray *)ft_lstlast(*ray->next)->content)->reflect_level += 1;
	((t_ray *)ft_lstlast(*ray->next)->content)->img_trace = 1;
}
