/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_ver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:55 by nachabi-          #+#    #+#             */
/*   Updated: 2025/12/26 16:14:43 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	handle_v_hit(t_mlx *m, t_ray *ray, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)(x / TILE);
	my = (int)(y / TILE);
	if (m->map[my][mx] == 1)
	{
		ray->v_x = x;
		ray->v_y = y;
		ray->v_door = 0;
		return (hypot(x - m->player.x, y - m->player.y));
	}
	if (m->map[my][mx] == 4)
	{
		ray->v_x = x;
		ray->v_y = y;
		ray->v_door = 1;
		return (hypot(x - m->player.x, y - m->player.y));
	}
	return (-1);
}

static double	vertical_loop(t_mlx *m, t_ray *ray, t_step *s)
{
	double	dist;

	while (s->x >= 0 && s->x < m->map_width * TILE
		&& s->y >= 0 && s->y < m->map_height * TILE)
	{
		dist = handle_v_hit(m, ray, s->x, s->y);
		if (dist >= 0)
			return (dist);
		s->x += s->x_step;
		s->y += s->y_step;
	}
	return (1e30);
}

double	get_vertical_hit(t_mlx *m, t_ray *ray)
{
	t_step	s;
	double	angle;
	double	px;
	double	py;
	int		facing_right;

	angle = ray->ray_angle;
	px = m->player.x;
	py = m->player.y;
	facing_right = (angle < M_PI_2 || angle > 3 * M_PI_2);
	s.x = floor(px / TILE) * TILE;
	if (facing_right)
		s.x += TILE;
	s.y = py + (s.x - px) * tan(angle);
	if (facing_right)
		s.x_step = TILE * 1;
	else
		s.x_step = TILE * -1;
	s.y_step = s.x_step * tan(angle);
	if (!facing_right)
		s.x -= 0.0001;
	return (vertical_loop(m, ray, &s));
}
