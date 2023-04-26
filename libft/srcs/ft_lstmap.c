/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haecho <haecho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:58 by siwolee           #+#    #+#             */
/*   Updated: 2022/11/19 10:36:28 by haecho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*node;

	if (!lst || !f)
		return (0);
	res = ft_lstnew((*f)(lst->content));
	if (!res)
		return (0);
	node = res;
	lst = lst->next;
	while (lst)
	{
		node->next = ft_lstnew((*f)(lst->content));
		if (!node->next)
		{
			ft_lstclear(&res, (*del));
			res = 0;
		}
		node = node->next;
		lst = lst->next;
	}
	node->next = 0;
	return (res);
}
