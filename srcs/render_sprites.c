#include "../includes/cub3d.h"
void sort_sprites(t_mlx *m)
{
    for (int i = 0; i < m->sprite_count - 1; i++)
        for (int j = i + 1; j < m->sprite_count; j++)
            if (m->sprites[i].distance < m->sprites[j].distance)
            {
                t_sprite tmp = m->sprites[i];
                m->sprites[i] = m->sprites[j];
                m->sprites[j] = tmp;
            }
}

void draw_sprite(t_mlx *m, t_sprite *sp)
{
    double dx = sp->x - m->player.x;
    double dy = sp->y - m->player.y;

    double dist = sqrt(dx * dx + dy * dy);
    sp->distance = dist;

    double angle = atan2(dy, dx) - m->player.dir;
    while (angle > M_PI) angle -= 2 * M_PI;
    while (angle < -M_PI) angle += 2 * M_PI;

    if (fabs(angle) > FOV / 2)
        return;

    double size = (TILE / dist) * (m->w_width / 2) / tan(FOV / 2);

    int sprite_screen_x = (m->w_width / 2) * (1 + tan(angle) / tan(FOV / 2));

    int draw_start_y = m->w_height / 2 - size / 2;
    int draw_end_y   = m->w_height / 2 + size / 2;

    t_tex *tex = &sp->frames[sp->frame];

    for (int x = 0; x < size; x++)
    {
        int screen_x = sprite_screen_x - size / 2 + x;
        if (screen_x < 0 || screen_x >= m->w_width)
            continue;

        double tex_x = (double)x / size * tex->width;

        if (m->all_rays.rays[screen_x].distance < dist)
            continue;

        for (int y = draw_start_y; y < draw_end_y; y++)
        {
            if (y < 0 || y >= m->w_height)
                continue;

            double tex_y = (double)(y - draw_start_y) / size * tex->height;
            int color = tex->addr[(int)tex_y * tex->width + (int)tex_x];

            if ((color & 0x00FFFFFF) != 0)
                mymlx_pixel_put(m, screen_x, y, color);
        }
    }
}

void render_sprites(t_mlx *m)
{
    for (int i = 0; i < m->sprite_count; i++)
    {
        double dx = m->sprites[i].x - m->player.x;
        double dy = m->sprites[i].y - m->player.y;
        m->sprites[i].distance = sqrt(dx*dx + dy*dy);
    }

    sort_sprites(m);

    for (int i = 0; i < m->sprite_count; i++)
        draw_sprite(m, &m->sprites[i]);
}
