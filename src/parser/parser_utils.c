/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:13:00 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/18 21:26:13 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	**nsplit(char *line, char delim, int expected)
{
	char	**parts;
	int		count;

	parts = ft_split(line, delim);
	if (!parts)
		return (NULL);
	count = 0;
	while (parts && parts[count])
		count++;
	if (count != expected)
	{
		ft_putstr_fd("miniRT: Incorrect number of parameters: ", 2);
		ft_putstr_fd(ft_strtrim(line, "\n"), 2);
		ft_putstr_fd("\n", 2);
		ft_free_arrays(parts);
		return (NULL);
	}
	return (parts);
}

void	dbfree(char **str)
{
	int i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])	
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}
