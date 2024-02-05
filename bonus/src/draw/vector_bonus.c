/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:07:07 by seongwol          #+#    #+#             */
/*   Updated: 2024/02/05 15:07:08 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

/**
 * 벡터를 각도만큼 회전하는 함수.
 * vector : vector
 * angle : radian scale 의 각도 parameter. 반시계 방향이 (+) 이지만, mlx 스케일에서 시계방향.
 * 만약 각도가 deg 스케일이면 deg_to_rad 를 이용해서 변환하자.
*/
t_vector	vector_rotate(t_vector vec, double angle)
{
	t_vector	res;

	res.x = vec.x * cos(-angle) - vec.y * sin(-angle);
	res.y = vec.x * sin(-angle) + vec.y * cos(-angle);
	return (res);
}

/* 벡터의 기울기를 반환, 기울기가 무한일 때는 아주 작은 숫자로 대체해서 에러를 피함. */
double	vector_gradient(t_vector vector)
{
	if (vector.x == 0)
		vector.x = 0.0000000000000001;
	return (vector.y / vector.x);
}

/* 벡터를 크기가 1인 단위 벡터로 변환. */
t_vector	vector_normalizing(t_vector vector)
{
	double		scale;
	t_vector	ret;

	scale = sqrt((pow(vector.x, 2) + pow(vector.y, 2)));
	ret.x = vector.x / scale;
	ret.y = vector.y / scale;
	return (ret);
}

/**
 * 벡터에 스케일을 곱해주는 함수.
*/
t_vector	vector_multiple(t_vector vector, double scale)
{
	return ((t_vector){vector.x * scale, vector.y * scale});
}

/* 벡터의 덧셈, 뺄셈, 외적을 관리해주는 함수 */
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
