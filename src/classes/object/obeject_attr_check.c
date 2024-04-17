/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obeject_attr_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:55:55 by math              #+#    #+#             */
/*   Updated: 2024/04/17 20:10:19 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_color(int color)
{
	if (color >= 0 && color <= 0xFFFFFF)
		return (EXIT_SUCCESS);
	ft_putstr_fd("miniRT: Color out of range: ", 2);
	return (EXIT_FAILURE);
}

int check_light_brightness(double b)
{
	if (b >= 0 && b <= 1)
		return (EXIT_SUCCESS);
	ft_putstr_fd("miniRT: Brightness out of range: ", 2);
	return (EXIT_FAILURE);
}

int	check_direction(t_vec3 vec)
{
	if (vector_length(vec) != 0)
		return (EXIT_SUCCESS);
	ft_putstr_fd("miniRT: Null direction: ", 2);
	return (EXIT_FAILURE);
}

int check_fov(int fov)
{
	if (fov >= 0 && fov <= 1)
		return (EXIT_SUCCESS);
	ft_putstr_fd("miniRT: FOV out of range: ", 2);
	return (EXIT_FAILURE);
}