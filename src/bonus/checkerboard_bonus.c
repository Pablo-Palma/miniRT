/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:16:33 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/19 07:09:23 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	apply_checkerboard_texture(t_vec3 point)
{
	const double	scale = 0.5;
	int	x = abs((int)floor(point.x * scale)) % 2;
	int	y = abs((int)floor(point.y * scale)) % 2;
	int	z = abs((int)floor(point.z * scale)) % 2;

	int	decision = (x ^ y ^ z);
	if (decision == 0)
		return(WHITE);
	else
		return(BLACK);
}

int	apply_checkerboard_texture_uv(double u, double v)
{
	const double scale = 10.0;
	int x = (int)(floor(u * scale)) % 2;
	int y = (int)(floor(v * scale)) % 2;
	int	color;

	if (x == y)
		color = WHITE;
	else
		color = BLACK;
	return (color);
}

int	apply_checkerboard_texture_uv_cyl(double u, double v, t_cyl cyl)
{
    double cuadroSize = cyl.radius / 2.0; // Esto determina el tamaño de los cuadros basado en el radio del cilindro

    // Calcular la repetición del patrón basado en el tamaño del cuadro
    double u_repeats = (2 * M_PI * cyl.radius) / cuadroSize; // Cuántos cuadros caben alrededor del cilindro
    double v_repeats = cyl.h / cuadroSize; // Cuántos cuadros caben a lo largo de la altura del cilindro

    // Aplicar la textura de tablero de ajedrez
    int x = (int)(floor(u * u_repeats)) % 2;
    int y = (int)(floor(v * v_repeats)) % 2;
    int color = (x == y) ? WHITE : BLACK;

    return color;
}
