/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:32:36 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/19 09:59:06 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	cleanup_and_exit(char **parts, char *error_msg, int r_value)
{
	if (error_msg)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (parts)
		ft_free_arrays(parts);
	return (r_value);
}

void	lst_mv_all_to_pool(t_list **pool, t_list **list,
		void (*clean)(void *node))
{
	t_list	*cur;

	if (!pool || !list)
		return ;
	while (*list)
	{
		cur = lst_strip_front(list);
		lst_mv_one_to_pool(pool, cur, clean);
	}
}

void	lst_mv_one_to_pool(t_list **pool, t_list *node,
		void (*clean)(void *node))
{
	if (!pool || !node)
		return ;
	if (clean)
		clean(node);
	ft_lstadd_back(pool, node);
}
