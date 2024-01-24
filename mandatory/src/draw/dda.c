#include "../../include/cub3d.h"

void	get_dist(t_point point, t_vector *dist, t_vector ray)
{
	if (ray.x == 0)
		dist->x = 1000000000;
	else
		dist->x = ft_abs(1 / ray.x);
	if (ray.y == 0)
		dist->y = 1000000000;
	else
		dist->y = ft_abs(1 / ray.y);
}

void	get_side(t_point point, t_vector *side, t_vector dist, t_vector ray)
{
	if (ray.x < 0)
		side->x = (point.player.x - (int)point.player.x) * dist.x;
	else if (point.sight.x > 0)
		side->x = ((int)point.player.x + 1 - point.player.x) * dist.x;
	if (ray.y < 0)
		side->y = (point.player.y - (int)point.player.y) * dist.y;
	else if (point.sight.y > 0)
		side->y = ((int)point.player.y + 1 - point.player.y) * dist.y;	
}

void	set_step(t_vector sight, int *step_x, int *step_y)
{
	if (sight.x < 0)
		*step_x = -1;
	else
		*step_x = 1;
	if (sight.y < 0)
		*step_y = -1;
	else
		*step_y = 1;	
}

int	ft_dda(t_data *data, t_vector *dist, t_vector *side, t_vector ray)
{
	int	map_x;
	int	map_y;
	int	step_x;
	int	step_y;
	int	side_wall;

	set_step(data->point.sight, &step_x, &step_y);
	map_x = (int)data->point.player.x;
	map_y = (int)data->point.player.y;
	while (data->map[map_y][map_x] != '1')
	{
		if (side->x < side->y)
		{
			side->x += dist->x;
			map_x += step_x;
			side_wall = 0;
		}
		else
		{
			side->y += dist->y;
			map_y += step_y;
			side_wall = 1;
		}
	}
	return (side_wall);
}

t_dda	get_wall_height(t_data *data, t_point point, t_vector ray)
{
	t_dda		dda;

	get_dist(point, &dda.dist, ray);
	get_side(point, &dda.side, dda.dist, ray);
	dda.side_wall = ft_dda(data, &dda.dist, &dda.side, ray);
	if (dda.side_wall == 0)
		dda.wall_dist = dda.side.x - dda.dist.x;
	else
		dda.wall_dist = dda.side.y - dda.dist.y;
	dda.height = 3 * WIN_VER / dda.wall_dist;
	return (dda);
}