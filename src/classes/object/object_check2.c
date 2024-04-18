/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:22:58 by math              #+#    #+#             */
/*   Updated: 2024/04/18 22:23:11 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_cam(t_cam *cam)
{
	if (!cam)
		return (EXIT_FAILURE);
	if (check_direction(cam->orientation) || check_fov(cam->fov))
		return (EXIT_FAILURE);
	if (check_unitary_vec(&cam->orientation))
		return (2);
	return (EXIT_SUCCESS);
}
