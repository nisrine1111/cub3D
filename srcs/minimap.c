#include "../includes/cub3d.h"

void draw_minimap(t_mlx *m)
{
    for (int y = 0; y < MAP_H; y++)
    {
        for (int x = 0; x < MAP_W; x++)
        {
            int color = (m->map[y][x] == 1 ? 0x222222 : 0xAAAAAA);
            int sx = x * TILE * MMAP_SCALE;
            int sy = y * TILE * MMAP_SCALE;

            for (int i = 0; i < TILE * MMAP_SCALE; i++)
                for (int j = 0; j < TILE * MMAP_SCALE; j++)
                    mymlx_pixel_put(m, sx + j, sy + i, color);
        }
    }
}

void draw_minimap_player(t_mlx *m)
{
    int px = m->player.x * MMAP_SCALE;
    int py = m->player.y * MMAP_SCALE;

    for (int y = -3; y <= 3; y++)
        for (int x = -3; x <= 3; x++)
            mymlx_pixel_put(m, px + x, py + y, 0xFF0000);
}

void draw_minimap_rays(t_mlx *m)
{
    int px = m->player.x * MMAP_SCALE;
    int py = m->player.y * MMAP_SCALE;

    for (int col = 0; col < NUM_RAYS; col++)
    {
        int rx = m->all_rays.rays[col].hit_x * MMAP_SCALE;
        int ry = m->all_rays.rays[col].hit_y * MMAP_SCALE;

        int dx = rx - px;
        int dy = ry - py;
        int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
        float x_inc = dx / (float)steps;
        float y_inc = dy / (float)steps;

        float xx = px;
        float yy = py;

        for (int i = 0; i < steps; i++)
        {
            mymlx_pixel_put(m, xx, yy, 0x00FF00);
            xx += x_inc;
            yy += y_inc;
        }
    }
}
