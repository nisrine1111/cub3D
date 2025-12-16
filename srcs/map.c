#include "../includes/cub3d.h"

void init_map(t_mlx *mlx, t_data *game)
{
    int y, x;

    mlx->map_width = game->grid_width;
    mlx->map_height = game->grid_height;

    mlx->map = malloc(sizeof(int *) * mlx->map_height);
    if (!mlx->map)
        exit(1);

    for (y = 0; y < mlx->map_height; y++)
    {
        mlx->map[y] = malloc(sizeof(int) * mlx->map_width);
        if (!mlx->map[y])
            exit(1);
    }

    for (y = 0; y < mlx->map_height; y++)
    {
        for (x = 0; x < mlx->map_width; x++)
        {
            char *c = &game->map[y][x];

            if (*c == '1')
                mlx->map[y][x] = 1;
            else if (*c == '0')
                mlx->map[y][x] = 0;
            else if (*c == '2')
                mlx->map[y][x] = 2;
            else if (*c == '4')
                mlx->map[y][x] = 4;
            else if (*c == '6')
                mlx->map[y][x] = 6;
            else if (*c == 'N' || *c == 'S' || *c == 'E' || *c == 'W')
            {
                (game->spawn_dir) = c;
                mlx->map[y][x] = 0;
            }
                
            else
                mlx->map[y][x] = 1;
        }
    }

    int count = 0;
    for (y = 0; y < mlx->map_height; y++)
        for (x = 0; x < mlx->map_width; x++)
            if (mlx->map[y][x] == 6)
                count++;

    mlx->sprite_count = count;
    mlx->sprites = malloc(sizeof(t_sprite) * count);
    if (!mlx->sprites)
        exit(1);

    int k = 0;
    for (y = 0; y < mlx->map_height; y++)
    {
        for (x = 0; x < mlx->map_width; x++)
        {
            if (mlx->map[y][x] == 6)
            {
                mlx->sprites[k].x = x * TILE + TILE / 2;
                mlx->sprites[k].y = y * TILE + TILE / 2;
                mlx->sprites[k].distance = 0;
                k++;
            }
        }
    }
}

void toggle_door(t_mlx *m)
{
    int mx = (int)((m->player.x + cos(m->player.dir) * DOOR_DISTANCE) / TILE);
    int my = (int)((m->player.y + sin(m->player.dir) * DOOR_DISTANCE) / TILE);

    if (mx < 0 || mx >= m->map_width || my < 0 || my >= m->map_height)
        return;
    if (m->map[my][mx] == 2){
        m->map[my][mx] = 3;
    }
    else if (m->map[my][mx] == 3)
        m->map[my][mx] = 2;
    if (m->map[my][mx] == 4){
        m->map[my][mx] = 5;
    }
    else if (m->map[my][mx] == 5)
        m->map[my][mx] = 4;
}
