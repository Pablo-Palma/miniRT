/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:50:35 by math              #+#    #+#             */
/*   Updated: 2024/03/19 00:52:15 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpiter(t_list *lst, void (*f)(void *), void *param)
{
	while (lst)
	{
		f(param);
		lst = lst->next;
	}
}