/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_method.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:03:50 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/13 07:35:02 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

//(x - xo)ˆ2 + (y - yo)ˆ2 + (z - zo)ˆ2 = rˆ2

typedef struct s_ray
{
	t_vec3	*origin;
	t_vec3	*direction;
	t_vec3	*intersection;
	t_obj	*obj;
}			t_ray;

t_ray	*ray(t_vec3 *origin, t_vec3 *direction)
{
	t_ray	*self;

	self = malloc(sizeof(t_ray));
	self->origin = origin;
	self->direction = direction;
	self->intersection = NULL;
	self->obj = NULL;
}

t_vec3	get_point(t_ray self, float t)
{
	return (vector_add(vector_scalar_mult(self.direction, t)), self.origin);
}

static int	touch_sphere(t_sphere sp, t_vec3 point)
{
	// get vector from center of sphere to 0,0,0
	// sum vector center
	// sum vecctor point

	if (point.x * point.x + point.y * point.y + point.z * point.z < /* ratio * ratio*/)
		return (1);
	return (0);

}

void	ray_propagate(t_list **ray_lst, t_list **obj, float res)
{
	float t;
	t_ray *ray;

	ray = (t_ray *)(*ray_lst)->content;
	t = 0;
	while (/* not reflected */ && /* t < MAX*/)
	{
		t += res;
	}
	ray->intersection = /* intersection point */;
	ray->obj = /* object intersected */;
	if (ray->obj != /* end of space */)
	{
		ft_lstaddback(ray_lst, ft_lstnew(ray(/* intersection point */,
												/* reflect direction */)));
		ray_propagate(ft_lstlast(ray_lst));
	}
	return ;
}