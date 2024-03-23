/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:18:01 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/18 19:34:36 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CHECKERBOARD_BONUS_H
# define	CHECKERBOARD_BONUS_H

# include "miniRT.h"

int	apply_checkerboard_texture(t_vec3 point);
int	apply_checkerboard_texture_uv(double u, double v);

#endif