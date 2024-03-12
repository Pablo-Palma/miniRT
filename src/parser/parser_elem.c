/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:24:57 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/12 17:16:20 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient(char *line, t_scene *scene)
{
	char 	**parts;
	double	intensity;
	int		color;

	parts = split_and_validate(line, 3, ' ');
	if (!parts)
		return(cleanup_and_exit(NULL, "Invalid ambient light format", 0));
	intensity = convert_to_double(parts[1], 0.0, 1.0);
	if (intensity < 0.0)
		return(cleanup_and_exit(parts, "Invalid intesity for ambient light", 0));
	color = convert_rgb_to_int(parts[2]);
	if (color < 0)
		return(cleanup_and_exit(parts, "Invalid RGB values for ambient light", 0));
	scene->ambient_light.intensity = intensity;
	scene->ambient_light.color = color;
	return(cleanup_and_exit(parts, NULL, 1));
}
