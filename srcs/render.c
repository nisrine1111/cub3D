#include "../includes/cub3d.h"

int render_frame(t_mlx *m)
{
    m->img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
    m->addr = mlx_get_data_addr(m->img, &m->bits_per_pixel, &m->line_lenght, &m->endian);

    cast_rays(m);
    m->frame_counter++;

    if (m->frame_counter % 10 == 0)
    {
        for (int i = 0; i < m->sprite_count; i++)
            m->sprites[i].frame = (m->sprites[i].frame + 1) % 4;
    }

    render_3d(m);
    render_sprites(m);
    draw_minimap(m);
    draw_minimap_rays(m);
    draw_minimap_player(m);

    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    mlx_destroy_image(m->mlx, m->img);
    return (0);
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

void load_sprites(t_mlx *m)
{
    int i;

    for (i = 0; i < m->sprite_count; i++)
    {
        // load all frames for sprite i
        load_texture(m, &m->sprites[i].frames[0], "./textures/torch1.xpm");
        load_texture(m, &m->sprites[i].frames[1], "./textures/torch2.xpm");
        load_texture(m, &m->sprites[i].frames[2], "./textures/torch3.xpm");
        load_texture(m, &m->sprites[i].frames[3], "./textures/torch4.xpm");

        m->sprites[i].frame = 0;
    }
}
