#include "../includes/cub3d.h"

double normalize_angle(double angle)
{
    double two_pi = 2 * M_PI;

    angle = fmod(angle, two_pi);
    if (angle <= 0)
        angle += two_pi;
    return angle;
}

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
	s.y_step = TILE * (facing_down ? 1 : -1);
	s.x_step = s.y_step / tan(angle);
	if (!facing_down)
		s.y -= 0.0001;
	return (horizontal_loop(m, ray, &s));
}

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
	s.x_step = TILE * (facing_right ? 1 : -1);
	s.y_step = s.x_step * tan(angle);
	if (!facing_right)
		s.x -= 0.0001;
	return (vertical_loop(m, ray, &s));
}
