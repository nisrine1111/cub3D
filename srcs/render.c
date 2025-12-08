#include "../includes/cub3d.h"

void render_frame(t_mlx *m)
{
    m->img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
    m->addr = mlx_get_data_addr(m->img, &m->bits_per_pixel, &m->line_lenght, &m->endian);

    cast_rays(m);
    render_3d(m);
    draw_minimap(m);
    draw_minimap_rays(m);
    draw_minimap_player(m);

    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    mlx_destroy_image(m->mlx, m->img);
}

void render_3d(t_mlx *m)
{
    int col = 0;

    while (col < NUM_RAYS)
    {
        t_ray *ray = &m->all_rays.rays[col];

        draw_textured_wall(m, col, ray);

        col++;
    }
}
