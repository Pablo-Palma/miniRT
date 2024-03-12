/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:32:36 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/12 17:08:16 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	cleanup_and_exit(char **parts, char *error_msg, int r_value)
{
	if(error_msg)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (parts)
		ft_free_arrays(parts);
	return (r_value);
}
