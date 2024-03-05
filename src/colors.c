/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:21:44 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/05 16:45:12 by pabpalma         ###   ########.fr       */
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

int	mix_colors(int	base_color, double diffuse, double specular)
{
	int	r = (base_color >> 16) & 0xFF;
	int	g = (base_color >> 8) & 0xFF;
	int	b = base_color & 0xFF;

	r = fmin(255, r * diffuse + 255 * specular);
	g = fmin(255, g * diffuse + 255 * specular);
	b = fmin(255, b * diffuse + 255 * specular);

	return (r << 16) | (g << 8) | b;
}
