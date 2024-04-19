/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:21:44 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/19 09:56:38 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	put_pixel_to_image(t_graph *graph, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = graph->addr + (y * graph->line_lenght + x * (graph->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	mix_colors(t_ambient_light ambient_light, int base_color, double diffuse,
	double specular)
{
	float	ambient;
	int		r;
	int		g;
	int		b;

	ambient = ambient_light.intensity;
	r = (base_color >> 16) & 0xFF;
	g = (base_color >> 8) & 0xFF;
	b = base_color & 0xFF;
	r = fmin(255, (r * ambient) + (r * diffuse) + (255 * specular));
	g = fmin(255, (g * ambient) + (g * diffuse) + (255 * specular));
	b = fmin(255, (b * ambient) + (b * diffuse) + (255 * specular));
	return ((r << 16) | (g << 8) | b);
}
