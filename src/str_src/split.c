#include "../../include/cub3d.h"

static size_t	my_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = 0;
	while (*(src + src_len))
		src_len++;
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (*(src + i) && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

static void	my_free_exit(char **res, int cnt_idx)
{
	while (cnt_idx >= 0)
		free(res[cnt_idx--]);
	free(res);
	exit (1);
}

static char	**make_wdspace(char const *s, char c, int *wdcnt)
{
	char	**res;

	*wdcnt = 0;
	while (*s)
	{
		if (*s != c)
		{
			(*wdcnt)++;
			while (*s != c && *s)
				s++;
			continue ;
		}
		s++;
	}
	res = malloc(sizeof(char *) * (*wdcnt + 1));
	if (res == NULL)
		exit_error("malloc failed", NULL);
	return (res);
}

static char	**make_chspace(char const *s, char c, char **res)
{
	size_t	ch_len;
	size_t	wd_idx;

	wd_idx = 0;
	while (*s)
	{
		ch_len = 0;
		if (*s != c)
		{
			while (*(s + ch_len) != c && *(s + ch_len))
				ch_len++;
			res[wd_idx] = malloc(sizeof(char) * (ch_len + 2));
			if (res[wd_idx] == 0)
				my_free_exit(res, wd_idx - 1);
			my_strlcpy(res[wd_idx++], s, ch_len + 2);
			s += ch_len;
			continue ;
		}
		s++;
	}
	res[wd_idx] = 0;
	return (res);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		wdcnt;

	if (s == NULL)
		return (NULL);
	while (*s && *s == c)
		s++;
	res = make_wdspace(s, c, &wdcnt);
	if (res == 0)
		return (0);
	res = make_chspace(s, c, res);
	return (res);
}
