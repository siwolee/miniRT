/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:53:00 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/02 16:22:02 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

t_list	*chk_list(t_list *lst, int fd)
{
	t_list	*temp;

	temp = lst;
	while (temp != 0 && temp->next != 0 && temp->fd != fd)
	{
		temp = temp->next;
	}
	if (temp->fd == fd)
		return (temp);
	temp->next = (t_list *)malloc(sizeof(t_list));
	if (!temp->next)
	{
		lst = lst->next;
		while (lst)
		{
			temp = (lst)->next;
			free((lst));
			lst = temp;
		}
		return (0);
	}
	temp->next->fd = fd;
	(temp->next->buf)[0] = 0;
	temp->next->next = NULL;
	return (temp->next);
}

t_list	*remove_list(t_list *lst, t_list *fd_lst)
{
	while ((lst)->next && (lst)->next != fd_lst)
	{
		lst = (lst)->next;
	}
	if ((lst)->next == fd_lst)
	{
		(lst)->next = fd_lst->next;
		free(fd_lst);
	}
	return (NULL);
}

void	delete_list(t_list *lst)
{
	t_list	*next;
	t_list	*temp;

	temp = lst->next;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	n;
	size_t	i;

	n = count * size;
	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

int	chk_n_idx(char buf[], char n)
{
	size_t	i;

	i = 0;
	if (!buf)
		return (-1);
	while (buf[i] && buf[i] != n)
		i++;
	if (buf[i] == n)
		return (i);
	return (-1);
}
