/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_constructor_attr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:55:55 by math              #+#    #+#             */
/*   Updated: 2024/04/19 20:00:38 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	constructor_color(int *color, char *line)
{
	char	**str_color;
	int		rgb[3];
	int		i;

	str_color = nsplit(line, ',', 3);
	if (!str_color)
		return (EXIT_FAILURE);
	rgb[0] = ft_atoi(str_color[0]);
	rgb[1] = ft_atoi(str_color[1]);
	rgb[2] = ft_atoi(str_color[2]);
	i = -1;
	while (++i < 3)
	{
		if (!(rgb[i] >= 0 && rgb[i] <= 255))
		{
			ft_putstr_fd("miniRT: Color out of range:", 2);
			return (EXIT_FAILURE);
		}
	}
	*color = ((rgb[0] << 16)
			| (rgb[1] << 8)
			| rgb[2]);
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
