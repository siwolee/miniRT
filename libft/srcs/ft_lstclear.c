/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haecho <haecho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:58 by siwolee           #+#    #+#             */
/*   Updated: 2022/11/19 10:59:52 by haecho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*temp;

	if (*lst)
	{
		node = *lst;
		while (node->next)
		{
			temp = node->next;
			(*del)(node->content);
			free(node);
			node = temp;
		}
		(*del)(node->content);
		free(node);
	}
	*lst = 0;
}
