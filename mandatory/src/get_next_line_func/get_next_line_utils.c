/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:17:02 by ilko              #+#    #+#             */
/*   Updated: 2024/01/06 21:38:58 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*my_strndup_gnl(const char *s1, int len)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(res + i) = *(s1 + i);
		i++;
	}
	*(res + i) = '\0';
	return (res);
}

void	*if_error_gnl(t_list **backup, t_list **cur_back)
{
	t_list	*pre;
	t_list	*head;

	pre = *backup;
	head = *backup;
	while (*backup != *cur_back)
	{
		pre = *backup;
		*backup = (*backup)->next;
	}
	free((*cur_back)->str);
	(*cur_back)->str = NULL;
	(*cur_back)->len = 0;
	(*cur_back)->fd = -1;
	if (*cur_back == head)
		*backup = head->next;
	else
		*backup = head;
	pre->next = (*cur_back)->next;
	free(*cur_back);
	*cur_back = NULL;
	return (NULL);
}

static t_list	*make_new(int fd)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->str = NULL;
	new->len = 0;
	new->fd = fd;
	new->next = NULL;
	return (new);
}

t_list	*check_fd_list(t_list **backup, int fd)
{
	t_list	*cur;

	cur = *backup;
	if (*backup == NULL)
	{
		cur = make_new(fd);
		if (cur == NULL)
			return (NULL);
		*backup = cur;
		return (cur);
	}
	while (cur != NULL && cur->fd != -1)
	{
		if (cur->fd == fd)
			return (cur);
		if (cur->next == NULL)
			break ;
		cur = cur->next;
	}
	cur->next = make_new(fd);
	if (cur->next == NULL)
		return (NULL);
	return (cur->next);
}
