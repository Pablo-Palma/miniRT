/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:13:00 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/17 13:18:52 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	convert_to_int(char *str, int min, int max)
{
	int	num;

	num = ft_atoi(str);
	if (num < min || num > max)
	{
		ft_putstr_fd("Error: Value out of range\n", 2);
		return (-1);
	}
	return (num);
}

double	convert_to_double(char *str, double min, double max)
{
	double	num;

	num = ft_atof(str);
	if (num < min || num > max)
	{
		ft_putstr_fd("Error: Value out of range\n", 2);
		return (-1.0);
	}
	return (num);
}
