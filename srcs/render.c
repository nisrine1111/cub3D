#include "../includes/cub3d.h"

static void draw_floor_and_ceiling(t_mlx *m)
{
    int x, y;

    for (y = 0; y < m->w_height / 2; y++)
        for (x = 0; x < m->w_width; x++)
            mymlx_pixel_put(m, x, y, m->ceiling_color);

    for (y = m->w_height / 2; y < m->w_height; y++)
        for (x = 0; x < m->w_width; x++)
            mymlx_pixel_put(m, x, y, m->floor_color);
}


int render_frame(t_mlx *m)
{
    m->img = mlx_new_image(m->mlx, m->w_width, m->w_height);
    m->addr = mlx_get_data_addr(m->img, &m->bits_per_pixel, &m->line_lenght, &m->endian);

    draw_floor_and_ceiling(m);
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
    mlx_mouse_move(m->mlx, m->win, m->w_width/2, m->w_height/2);
    return (0);
}

void render_3d(t_mlx *m)
{
    int col = 0;

    while (col < m->num_rays)
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
        load_texture(m, &m->sprites[i].frames[0], "./textures/torch1.xpm");
        load_texture(m, &m->sprites[i].frames[1], "./textures/torch2.xpm");
        load_texture(m, &m->sprites[i].frames[2], "./textures/torch3.xpm");
        load_texture(m, &m->sprites[i].frames[3], "./textures/torch4.xpm");

        m->sprites[i].frame = 0;
    }
}
