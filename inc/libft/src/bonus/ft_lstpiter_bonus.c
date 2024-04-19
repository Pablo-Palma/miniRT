/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpiter_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:50:35 by math              #+#    #+#             */
/*   Updated: 2024/04/19 19:38:04 by mamagalh@st      ###   ########.fr       */
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
