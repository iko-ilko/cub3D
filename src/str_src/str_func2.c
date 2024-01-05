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