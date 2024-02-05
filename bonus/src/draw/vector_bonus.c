/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:07:07 by seongwol          #+#    #+#             */
/*   Updated: 2024/02/05 16:31:57 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute_bonus.h"

t_vector	vector_rotate(t_vector vec, double angle)
{
	t_vector	res;

	res.x = vec.x * cos(-angle) - vec.y * sin(-angle);
	res.y = vec.x * sin(-angle) + vec.y * cos(-angle);
	return (res);
}

double	vector_gradient(t_vector vector)
{
	if (vector.x == 0)
		vector.x = 0.0000000000000001;
	return (vector.y / vector.x);
}

t_vector	vector_normalizing(t_vector vector)
{
	double		scale;
	t_vector	ret;

	scale = sqrt((pow(vector.x, 2) + pow(vector.y, 2)));
	ret.x = vector.x / scale;
	ret.y = vector.y / scale;
	return (ret);
}

t_vector	vector_multiple(t_vector vector, double scale)
{
	return ((t_vector){vector.x * scale, vector.y * scale});
}

t_vector	vector_calculate(t_vector v1, t_vector v2, int sign)
{
	t_vector	res;

	if (sign == PLUS)
	{
		res.x = v1.x + v2.x;
		res.y = v1.y + v2.y;
	}
	else
	{
		res.x = v1.x - v2.x;
		res.y = v1.y - v2.y;
	}
	return (res);
}
