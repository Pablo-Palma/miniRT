/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:18:50 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/11 18:00:09 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	OBJECT_H
# define OBJECT_H

typedef struct	s_object_node
{
	void	*content;
	char	type;
	struct	s_object_node	*prev;
	struct	s_object_node	*next;
}				t_object_node;

typedef struct	s_object_list
{
	struct	s_object_node	*head;
	struct	s_object_node	*tail;
	int						size;
}				t_object_list;

#endif
