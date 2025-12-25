#include "../includes/cub3d.h"

void cast_rays(t_mlx *mymlx)
{
    double ray_angle;
    double angle_step;
    int col;

    angle_step = FOV / mymlx->num_rays;
    col = 0;
    ray_angle = mymlx->player.dir - (FOV / 2);

    while (col < mymlx->num_rays)
    {
        ray_angle = normalize_angle(ray_angle);

        mymlx->all_rays.rays[col].ray_angle = ray_angle;
        cast_single_ray(mymlx, &mymlx->all_rays.rays[col]);
        ray_angle += angle_step;
        col++;
    }
}
