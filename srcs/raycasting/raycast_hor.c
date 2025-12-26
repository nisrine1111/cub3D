/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_hor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:28 by nachabi-          #+#    #+#             */
/*   Updated: 2025/12/26 16:07:42 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	handle_h_hit(t_mlx *m, t_ray *ray, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)(x / TILE);
	my = (int)(y / TILE);
	if (m->map[my][mx] == 1)
	{
		ray->h_x = x;
		ray->h_y = y;
		ray->h_door = 0;
		return (hypot(x - m->player.x, y - m->player.y));
	}
	if (m->map[my][mx] == 2)
	{
		ray->h_x = x;
		ray->h_y = y;
		ray->h_door = 1;
		return (hypot(x - m->player.x, y - m->player.y));
	}
	return (-1);
}

static double	horizontal_loop(t_mlx *m, t_ray *ray, t_step *s)
{
	double	dist;

	while (s->x >= 0 && s->x < m->map_width * TILE
		&& s->y >= 0 && s->y < m->map_height * TILE)
	{
		dist = handle_h_hit(m, ray, s->x, s->y);
		if (dist >= 0)
			return (dist);
		s->x += s->x_step;
		s->y += s->y_step;
	}
	return (1e30);
}

double	get_horizontal_hit(t_mlx *m, t_ray *ray)
{
	t_step	s;
	double	angle;
	double	px;
	double	py;
	int		facing_down;

	angle = ray->ray_angle;
	px = m->player.x;
	py = m->player.y;
	facing_down = (angle > 0 && angle < M_PI);
	s.y = floor(py / TILE) * TILE;
	if (facing_down)
		s.y += TILE;
	s.x = px + (s.y - py) / tan(angle);
	if (facing_down)
		s.y_step = TILE * 1;
	else
		s.y_step = TILE * -1;
	s.x_step = s.y_step / tan(angle);
	if (!facing_down)
		s.y -= 0.0001;
	return (horizontal_loop(m, ray, &s));
}
