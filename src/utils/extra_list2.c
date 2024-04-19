/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:41:18 by math              #+#    #+#             */
/*   Updated: 2024/04/19 00:41:31 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_list	*lst_getpool_node(t_list **pool, void *(*new)(void *),
		void (*update)(void *, void *), void *content)
{
	t_list	*new_node;

	if (!pool)
		return (NULL);
	new_node = lst_strip_back(pool);
	if (!new_node)
		return (ft_lstnew(new (content)));
	if (update)
		update(new_node->content, content);
	return (new_node);
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
