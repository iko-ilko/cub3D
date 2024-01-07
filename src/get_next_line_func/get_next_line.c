/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:55:53 by ilko              #+#    #+#             */
/*   Updated: 2024/01/07 16:09:05 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static void	cat_backup(t_list **backup, char *buf, int rd_size)
{
	int		i;
	int		j;
	char	*temp;

	while ((*backup)->len > 0 && *((*backup)->str + (*backup)->len))
		(*backup)->len++;
	temp = malloc(sizeof(char) * ((*backup)->len + rd_size + 1));
	if (temp == NULL)
		return ;
	i = -1;
	while (++i < (*backup)->len)
		*(temp + i) = *((*backup)->str + i);
	j = -1;
	while (++j < rd_size)
		*(temp + i + j) = *(buf + j);
	*(temp + i + j) = '\0';
	free((*backup)->str);
	(*backup)->str = temp;
	(*backup)->len = i + j;
}

static int	check_nl(t_list **backup, char **res)
{
	int		i;
	char	*temp;

	i = -1;
	while ((*backup)->len != 0 && *((*backup)->str + ++i))
	{
		if (*((*backup)->str + i) == '\n')
		{
			*res = my_strndup_gnl((*backup)->str, i + 1);
			if (*res == NULL)
				return (-1);
			temp = my_strndup_gnl((*backup)->str + i + 1, (*backup)->len - i - 1);
			if (temp == NULL)
			{
				free(*res);
				*res = NULL;
				return (-1);
			}
			free((*backup)->str);
			(*backup)->str = temp;
			(*backup)->len = (*backup)->len - i - 1;
			return (0);
		}
	}
	return (1);
}

static int	if_rd_size_is_zero_less(t_list **backup, int rd_size, char **res)
{
	if (rd_size < 0)
		return (-1);
	if (rd_size == 0)
	{
		if ((*backup)->len == 0)
			return (-1);
		*res = my_strndup_gnl((*backup)->str, (*backup)->len);
		if (*res == NULL)
			return (-1);
		(*backup)->len -= (*backup)->len;
	}
	return (1);
}

static int	roop_read(t_list **cur_back, char **res, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		rd_size;

	rd_size = 1;
	while (rd_size)
	{
		rd_size = read(fd, buf, BUFFER_SIZE);
		if (if_rd_size_is_zero_less(cur_back, rd_size, res) == -1)
			return (-1);
		buf[BUFFER_SIZE] = '\0';
		cat_backup(cur_back, buf, rd_size);
		if (check_nl(cur_back, res) == -1)
			return (-1);
		if (*res != NULL)
		{
			if ((*cur_back)->str == NULL)
				return (-1);
			return (1);
		}
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*backup;
	t_list			*cur_back;
	char			*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	cur_back = check_fd_list(&backup, fd);
	if (cur_back == NULL)
		return (NULL);
	res = 0;
	if (check_nl(&cur_back, &res) == -1)
		return (if_error_gnl(&backup, &cur_back));
	if (res != NULL)
	{
		if (cur_back->str == NULL)
			if_error_gnl(&backup, &cur_back);
		return (res);
	}
	if (roop_read(&cur_back, &res, fd) == -1)
		return (if_error_gnl(&backup, &cur_back));
	if (res != NULL && cur_back->str == NULL)
		if_error_gnl(&backup, &cur_back);
	return (res);
}
