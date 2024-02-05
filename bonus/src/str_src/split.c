/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:26:31 by ilko              #+#    #+#             */
/*   Updated: 2024/02/05 16:28:49 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static void	my_free_exit(char **res, int cnt_idx)
{
	while (cnt_idx >= 0)
		free(res[cnt_idx--]);
	free(res);
	exit_error(MALLOC_FAILED, NULL);
}

static int	is_separator(char c, char *sepa)
{
	while (*sepa)
	{
		if (*sepa == c)
			return (1);
		sepa++;
	}
	return (0);
}

static char	**make_wdspace(char *s, char *separators, int *wdcnt)
{
	char	**res;

	*wdcnt = 0;
	while (*s)
	{
		if (!is_separator(*s, separators))
		{
			(*wdcnt)++;
			while (!is_separator(*s, separators) && *s)
				s++;
			continue ;
		}
		s++;
	}
	res = malloc(sizeof(char *) * (*wdcnt + 1));
	if (res == NULL)
		exit_error(MALLOC_FAILED, NULL);
	return (res);
}

static char	**make_chspace(char *s, char *separators, char **res)
{
	int	ch_len;
	int	wd_idx;

	wd_idx = 0;
	while (*s)
	{
		ch_len = 0;
		if (!is_separator(*s, separators))
		{
			while (!is_separator(*(s + ch_len), separators) && *(s + ch_len))
				ch_len++;
			res[wd_idx] = malloc(sizeof(char) * (ch_len + 1));
			if (res[wd_idx] == NULL)
				my_free_exit(res, wd_idx - 1);
			my_strlcpy(res[wd_idx++], s, ch_len + 1);
			s += ch_len;
			continue ;
		}
		s++;
	}
	res[wd_idx] = 0;
	return (res);
}

char	**my_split(char *s, char *sepa)
{
	char	**res;
	int		wdcnt;

	if (s == NULL || sepa == NULL)
	{
		res = malloc(sizeof(char *));
		res[0] = NULL;
		return (res);
	}
	while (*s && is_separator(*s, sepa))
		s++;
	res = make_wdspace(s, sepa, &wdcnt);
	res = make_chspace(s, sepa, res);
	return (res);
}
