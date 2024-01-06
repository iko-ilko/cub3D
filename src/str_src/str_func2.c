#include "../../include/cub3d.h"

int	my_atoi(char *str)
{
	int	result;
	int	sign;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		sign = 44 - *str++;
	result = 0;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + *(str++) - '0';
	return (result * sign);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}