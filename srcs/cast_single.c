#include "../includes/cub3d.h"

void cast_single_ray(t_mlx *mymlx, t_ray *ray)
{
    ray->hit_door = 0;
    ray->ray_angle = normalize_angle(ray->ray_angle);

    double h_dist = get_horizontal_hit(mymlx, ray);
    double v_dist = get_vertical_hit(mymlx, ray);

    if (h_dist < v_dist)
    {
        ray->hit_x = ray->h_x;
        ray->hit_y = ray->h_y;
        ray->distance = h_dist;
        ray->hit_side = 0;
        ray->hit_door = ray->h_door;
        ray->wall_x = fmod(ray->hit_x / TILE, 1.0);
    }
    else
    {
        ray->hit_x = ray->v_x;
        ray->hit_y = ray->v_y;
        ray->distance = v_dist;
        ray->hit_side = 1;
        ray->hit_door = ray->v_door;
        ray->wall_x = fmod(ray->hit_y / TILE, 1.0);
    }
}