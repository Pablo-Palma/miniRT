/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:21:05 by math              #+#    #+#             */
/*   Updated: 2024/03/26 18:20:15 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_list *lst_strip_back(t_list **list)
{
    t_list  *cur_node;
    t_list  *strip_node;
    
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

t_list *lst_strip_front(t_list **list)
{
    t_list  *strip_node;
    
    if (!list || !*list)
        return (NULL);
    strip_node = *list;
    *list = strip_node->next;
    return (strip_node);
}

t_list  *lst_strip_node(t_list **list, t_list *node)
{
    t_list  *prev;
    t_list  *cur;

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

t_list  **lst_create(void)
{
    t_list **pool;

    pool = (t_list **) malloc(sizeof(t_list *));
    *pool = NULL;
    return (pool);
}

t_list  *lst_getpool_node(t_list **pool, void *(*new)(void *), void (*update)(void *, void *), void *content)
{
    t_list *new_node;

    if (!pool)
        return (NULL);
    new_node = lst_strip_back(pool);
    if (!new_node)
        return (ft_lstnew(new(content)));
    if (update)
        update(new_node->content, content);
    return (new_node);
}

void    lst_mv_one_to_pool(t_list **pool, t_list *node, void (*clean)(void *node))
{
    if (!pool || !node)
        return ;
    if (clean)
        clean(node);
    ft_lstadd_back(pool, node);
}

void    lst_mv_all_to_pool(t_list **pool, t_list **list, void (*clean)(void *node))
{
    t_list  *cur;

    if (!pool || !list)
        return ;
    while (*list)
    {
        cur = lst_strip_front(list);
        lst_mv_one_to_pool(pool, cur, clean);
    }
}