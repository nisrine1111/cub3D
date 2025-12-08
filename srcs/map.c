#include "../includes/cub3d.h"

void init_map(t_mlx *mymlx)
{
    int i = 0;
    int j;

    int tmp[MAP_H][MAP_W] = {
        // {1, 1, 1, 1, 1, 1, 1, 1},
        // {1, 0, 0, 1, 0, 1, 1, 1},
        // {1, 0, 0, 0, 2, 0, 1, 1},
        // {1, 1, 0, 0, 0, 0, 1, 1},
        // {1, 0, 0, 0, 0, 1, 0, 1},
        // {1, 0, 0, 1, 0, 0, 1, 1},
        // {1, 0, 0, 1, 1, 1, 1, 1},
        // {1, 1, 1, 1, 1, 1, 1, 1}

        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 4, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 3, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };
    
    while (i < MAP_H){
        j = 0;
        while (j < MAP_W){
            mymlx->map[i][j] = tmp[i][j];
            j++;
        }   
        i++;
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
