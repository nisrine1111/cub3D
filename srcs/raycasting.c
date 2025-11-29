#include "../includes/cub3d.h"

double normalize_angle(double angle)
{
    double two_pi = 2 * M_PI;

    angle = fmod(angle, two_pi);
    if (angle <= 0)
        angle += two_pi;
    return angle;
}

double get_horizontal_hit(t_mlx *m, t_ray *ray)
{
    double angle = ray->ray_angle;
    double px = m->player.x;
    double py = m->player.y;

    int facing_down = (angle > 0 && angle < M_PI);
    int facing_up = !facing_down;

    double y_inter = floor(py / TILE) * TILE;
    if (facing_down)
        y_inter += TILE;

    double x_inter = px + (y_inter - py) / tan(angle);

    double y_step = TILE * (facing_down ? 1 : -1);
    double x_step = y_step / tan(angle);

    double x = x_inter;
    double y = y_inter + (facing_up ? -0.0001 : 0);

    while (x >= 0 && x < MAP_W * TILE && y >= 0 && y < MAP_H * TILE)
    {
        int mx = (int)(x / TILE);
        int my = (int)(y / TILE);

        if (m->map[my][mx] == 1)
        {
            ray->h_x = x;
            ray->h_y = y;
            return hypot(x - px, y - py);
        }
        x += x_step;
        y += y_step;
    }

    return 1e30;
}

double get_vertical_hit(t_mlx *m, t_ray *ray)
{
    double angle = ray->ray_angle;
    double px = m->player.x;
    double py = m->player.y;

    int facing_right = (angle < M_PI_2 || angle > 3 * M_PI_2);
    int facing_left = !facing_right;

    double x_inter = floor(px / TILE) * TILE;
    if (facing_right)
        x_inter += TILE;

    double y_inter = py + (x_inter - px) * tan(angle);

    double x_step = TILE * (facing_right ? 1 : -1);
    double y_step = x_step * tan(angle);

    double x = x_inter + (facing_left ? -0.0001 : 0);
    double y = y_inter;

    while (x >= 0 && x < MAP_W * TILE && y >= 0 && y < MAP_H * TILE)
    {
        int mx = (int)(x / TILE);
        int my = (int)(y / TILE);

        if (m->map[my][mx] == 1)
        {
            ray->v_x = x;
            ray->v_y = y;
            return hypot(x - px, y - py);
        }
        x += x_step;
        y += y_step;
    }

    return 1e30;
}
