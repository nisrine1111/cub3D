#include "../includes/cub3d.h"

void init_map(t_mlx *mymlx)
{
    int i = 0, j;

    int tmp[MAP_H][MAP_W] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 4, 6, 0, 0, 0, 1},
        {1, 1, 1, 6, 6, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 6, 1},
        {1, 2, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    while (i < MAP_H) {
        j = 0;
        while (j < MAP_W) {
            mymlx->map[i][j] = tmp[i][j];
            j++;
        }
        i++;
    }

    int count = 0;

    for (int y = 0; y < MAP_H; y++)
    {
        for (int x = 0; x < MAP_W; x++)
        {
            if (mymlx->map[y][x] == 6)
                count++;
        }
    }

    mymlx->sprite_count = count;

    mymlx->sprites = malloc(sizeof(t_sprite) * count);
    if (!mymlx->sprites)
        exit(1);

    int k = 0;

    for (int y = 0; y < MAP_H; y++)
    {
        for (int x = 0; x < MAP_W; x++)
        {
            if (mymlx->map[y][x] == 6)
            {
                mymlx->sprites[k].x = x * TILE + TILE / 2;
                mymlx->sprites[k].y = y * TILE + TILE / 2;
                mymlx->sprites[k].distance = 0;
                k++;
            }
        }
    }
}

void toggle_door(t_mlx *m)
{
    int mx = (int)((m->player.x + cos(m->player.dir) * DOOR_DISTANCE) / TILE);
    int my = (int)((m->player.y + sin(m->player.dir) * DOOR_DISTANCE) / TILE);

    if (mx < 0 || mx >= MAP_W || my < 0 || my >= MAP_H)
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
