/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bhaskara.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:54:07 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/19 12:18:23 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_bhaskara(t_bhaskara *eq)
{
	eq->sqrt_discriminant = sqrt(eq->discriminant);
	eq->t0 = (-eq->b - eq->sqrt_discriminant) / (2 * eq->a);
	eq->t1 = (-eq->b + eq->sqrt_discriminant) / (2 * eq->a);
}
