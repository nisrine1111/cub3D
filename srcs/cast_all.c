#include "../includes/cub3d.h"

void cast_rays(t_mlx *mymlx)
{
    double ray_angle;
    double angle_step = FOV / NUM_RAYS;
    int col = 0;

    ray_angle = mymlx->player.dir - (FOV / 2);

    while (col < NUM_RAYS)
    {
        ray_angle = normalize_angle(ray_angle);

        mymlx->all_rays.rays[col].ray_angle = ray_angle;

        cast_single_ray(mymlx, &mymlx->all_rays.rays[col]);
        ray_angle += angle_step;
        col++;
    }
}