/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:58:34 by ilko              #+#    #+#             */
/*   Updated: 2024/01/06 21:40:30 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_back_list
{
	char				*str;
	int					len;
	int					fd;
	struct s_back_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	*if_error_gnl(t_list **backup, t_list **cur_back);
char	*my_strndup_gnl(const char *s1, int len);
t_list	*check_fd_list(t_list **backup, int fd);

#endif
