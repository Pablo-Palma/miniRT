/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 08:13:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/23 08:24:41 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int bonus_colors(int material_color, int reflected_color, float reflective)
{
	int r_material = (material_color >> 16) & 0xFF;
    int g_material = (material_color >> 8) & 0xFF;
    int b_material = material_color & 0xFF;

    int r_reflected = (reflected_color >> 16) & 0xFF;
    int g_reflected = (reflected_color >> 8) & 0xFF;
    int b_reflected = reflected_color & 0xFF;

    // Calcular los nuevos componentes de color
    int r_final = (int)((r_reflected * reflective) + (r_material * (1 - reflective)));
    int g_final = (int)((g_reflected * reflective) + (g_material * (1 - reflective)));
    int b_final = (int)((b_reflected * reflective) + (b_material * (1 - reflective)));

    // Asegurarse de que los componentes están en el rango [0, 255]
    r_final = r_final > 255 ? 255 : r_final;
    g_final = g_final > 255 ? 255 : g_final;
    b_final = b_final > 255 ? 255 : b_final;

    // Combinar los componentes en un entero
    return (r_final << 16) | (g_final << 8) | b_final;
}
