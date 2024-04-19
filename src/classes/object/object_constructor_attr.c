/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_constructor_attr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:55:55 by math              #+#    #+#             */
/*   Updated: 2024/04/19 10:29:10 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	constructor_color(int *color, char *line)
{
	char	**str_color;

	str_color = nsplit(line, ',', 3);
	if (!str_color)
		return (EXIT_FAILURE);
	*color = ((ft_atoi(str_color[0]) << 16) | (ft_atoi(str_color[1]) << 8)
			| (ft_atoi(str_color[2])));
	dbfree(str_color);
	return (EXIT_SUCCESS);
}

int	constructor_vec(t_vec3 *vec, char *line)
{
	char	**str_vec;

	str_vec = nsplit(line, ',', 3);
	if (!str_vec)
		return (EXIT_FAILURE);
	*vec = (t_vec3){ft_atof(str_vec[0]), ft_atof(str_vec[1]),
		ft_atof(str_vec[2])};
	dbfree(str_vec);
	return (EXIT_SUCCESS);
}
