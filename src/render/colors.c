/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:21:44 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/15 05:32:14 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int	convert_rgb_to_int(char *rgb_str)
{
	char **rgb_parts;
	int	r;
	int	g;
	int	b;

	rgb_parts = ft_split(rgb_str, ',');
	if(!rgb_parts)
	{
		ft_putstr_fd("Error: Invlaid RGB format\n", 2);
		return(-1);
	}
	r = convert_to_int(rgb_parts[0], 0, 255);
	g = convert_to_int(rgb_parts[1], 0, 255);
	b = convert_to_int(rgb_parts[2], 0, 255);

	ft_free_arrays(rgb_parts);

	if (r == -1 || b == -1 || b == -1)
		return(-1);
	return ((r << 16) | (g << 8) | b);
}

void	put_pixel_to_image(t_graph *graph, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = graph->addr + (y * graph->line_lenght + x * (graph->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	mix_colors(t_ambient_light ambient_light, int	base_color, double diffuse, double specular)
{
	int	ambient = ambient_light.intensity;
	int	r = (base_color >> 16) & 0xFF;
	int	g = (base_color >> 8) & 0xFF;
	int	b = base_color & 0xFF;

	double	ambient_r = ambient * ((ambient_light.color >> 16) & 0xFF);
	double	ambient_g = ambient * ((ambient_light.color >> 8) & 0xFF);
	double	ambient_b = ambient * (ambient_light.color  & 0xFF);

	r = fmin(255, r * diffuse + 255 * specular + ambient_r);
	g = fmin(255, g * diffuse + 255 * specular + ambient_g);
	b = fmin(255, b * diffuse + 255 * specular + ambient_b);

	return (r << 16) | (g << 8) | b;
}
