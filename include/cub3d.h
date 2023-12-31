#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_pre_data
{
	int		y_size;
	char	**map;
}	t_pre_data;

/* preprocess.c */
void	init_pre_data(t_pre_data *data);
char	**get_map(t_pre_data *data, char *file);
void	check_arv(t_pre_data *data, int arc, char **arv);


/* util.c */
void	exit_error(char *str, char *reason);
void	one_free(char **p);


/* str_func.c */
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);

/* split.c */
char	**ft_split(char *s, char c);


#endif