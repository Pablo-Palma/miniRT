/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_print2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:20:06 by math              #+#    #+#             */
/*   Updated: 2024/04/18 23:20:24 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_cylinder(void *obj)
{
	t_cyl	*cylinder;

	cylinder = (t_cyl *)obj;
	printf("Cylinder:\n");
	printf("\tCenter: (%.2f, %.2f, %.2f)\n", cylinder->center.x,
		cylinder->center.y, cylinder->center.z);
	printf("\tDirection: (%.2f, %.2f, %.2f)\n", cylinder->dir.x,
		cylinder->dir.y, cylinder->dir.z);
	printf("\tRadius: %.2f\n", cylinder->radius);
	printf("\tHeight: %.2f\n", cylinder->h);
	printf("\tColor: (%d, %d, %d)\n", (cylinder->color >> 16) & 0xFF,
		(cylinder->color >> 8) & 0xFF, cylinder->color & 0xFF);
}
