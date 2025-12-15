#include "../includes/cub3d.h"

void init_player(t_mlx *mlx, t_data *game)
{
    mlx->player.x = game->spawn_x * TILE;
    mlx->player.y = game->spawn_y * TILE;

    char *c = game->spawn_dir;
    if (*c == 'N')
        mlx->player.dir = M_PI * 1.5;
    else if (*c == 'S')
        mlx->player.dir = M_PI / 2;
    else if (*c == 'W')
        mlx->player.dir = M_PI;
    else if (*c == 'E')
        mlx->player.dir = 0;
}

void update_player_movement(t_mlx *mymlx)
{
    mymlx->player.dir += mymlx->player.turn_dir * ROT_SPEED;

    float move_step = mymlx->player.move_dir * MOVE_SPEED;
    float move_x = cos(mymlx->player.dir) * move_step;
    float move_y = sin(mymlx->player.dir) * move_step;

    float strafe_step = mymlx->player.strafe_dir * MOVE_SPEED;
    float strafe_x = cos(mymlx->player.dir + M_PI / 2) * strafe_step;
    float strafe_y = sin(mymlx->player.dir + M_PI / 2) * strafe_step;

    float next_x = mymlx->player.x + move_x + strafe_x;
    float next_y = mymlx->player.y + move_y + strafe_y;

    if (can_move(mymlx, next_x, mymlx->player.y))
        mymlx->player.x = next_x;
    if (can_move(mymlx, mymlx->player.x, next_y))
        mymlx->player.y = next_y;
}
