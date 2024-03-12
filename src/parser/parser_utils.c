/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:13:00 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/12 17:12:03 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char **split_and_validate(char *line, int expected, char delim)
{
	char	**parts = ft_split(line, delim);
	int		count = 0;

	while (parts && parts[count])
		count++;
	if (count != expected)
	{
		ft_putstr_fd("Error: Incorrect number of parameters\n", 2);
		ft_free_arrays(parts);
		return(NULL);
	}
	return(parts);
}

int	convert_to_int(char *str, int min, int max)
{
	int	num;

	num = ft_atoi(str);
	if (num < min || num > max)
	{
		ft_putstr_fd("Error: Value out of range\n", 2);
		return(-1);
	}
	return(num);
}

double	convert_to_double(char *str, double min, double max)
{
	double	num = ft_atof(str);

	if (num < min || num > max)
	{
		ft_putstr_fd("Error: Value out of range\n", 2);
		return(-1.0);
	}
	return(num);
}
