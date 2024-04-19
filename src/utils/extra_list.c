/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:21:05 by math              #+#    #+#             */
/*   Updated: 2024/04/19 17:43:08 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_list	*lst_strip_back(t_list **list)
{
	t_list	*cur_node;
	t_list	*strip_node;

	if (!list || !*list)
		return (NULL);
	cur_node = *list;
	if (!cur_node->next)
	{
		*list = NULL;
		return (cur_node);
	}
	while (cur_node->next->next)
		cur_node = cur_node->next;
	strip_node = cur_node->next;
	cur_node->next = NULL;
	return (strip_node);
}

t_list	*lst_strip_front(t_list **list)
{
	t_list	*strip_node;

	if (!list || !*list)
		return (NULL);
	strip_node = *list;
	*list = strip_node->next;
	strip_node->next = NULL;
	return (strip_node);
}

t_list	*lst_strip_node(t_list **list, t_list *node)
{
	t_list	*prev;
	t_list	*cur;

	if (!list || !node)
		return (NULL);
	prev = NULL;
	cur = *list;
	while (cur != node)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur != node)
		return (NULL);
	if (!prev)
		return (lst_strip_front(list));
	if (!cur->next)
		return (lst_strip_back(list));
	prev->next = cur->next;
	cur->next = NULL;
	return (cur);
}

t_list	**lst_create(void)
{
	t_list	**node_list;

	node_list = (t_list **)malloc(sizeof(t_list *));
	*node_list = NULL;
	return (node_list);
}

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
