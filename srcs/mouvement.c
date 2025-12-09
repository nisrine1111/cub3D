#include "../includes/cub3d.h"

int is_wall(t_mlx *m, float x, float y)
{
    int map_x = (int)(x / TILE);
    int map_y = (int)(y / TILE);

    if (map_x < 0 || map_x >= MAP_W || map_y < 0 || map_y >= MAP_H)
        return (1);

    int tile = m->map[map_y][map_x];

    if (tile == 1)
        return 1;
    if (tile == 2)
        return 1;
    return 0;
}


int can_move(t_mlx *m, float nx, float ny)
{
    float r = PLAYER_RADIUS;

    if (is_wall(m, nx + r, ny + r)) return 0;
    if (is_wall(m, nx - r, ny + r)) return 0;
    if (is_wall(m, nx + r, ny - r)) return 0;
    if (is_wall(m, nx - r, ny + r)) return 0;

    return 1;
}

int handle_key(int keycode, t_mlx *mymlx)
{
    mymlx->player.turn_dir = 0;
    mymlx->player.move_dir = 0;
    mymlx->player.strafe_dir = 0;

    if (keycode == KEY_W)
        mymlx->player.move_dir = 1;
    else if (keycode == KEY_S)
        mymlx->player.move_dir = -1;

    if (keycode == KEY_A)
        mymlx->player.strafe_dir = -1;
    else if (keycode == KEY_D)
        mymlx->player.strafe_dir = 1;

    if (keycode == KEY_LEFT)
        mymlx->player.turn_dir = -1;
    else if (keycode == KEY_RIGHT)
        mymlx->player.turn_dir = 1;

    if (keycode == KEY_E)
        toggle_door(mymlx);

    
    if (keycode == KEY_ESC)
        exit(0);

    update_player_movement(mymlx);
    render_frame(mymlx);
    return 0;
}

int mouse_move(int x, int y, t_mlx *m)
{
    (void)y;

    int center_x = WIDTH / 2;
    int dx = x - center_x;

    if (dx == 0)
        return (0);

    m->player.dir += dx * m->mouse_sensitivity;
    m->player.dir = normalize_angle(m->player.dir);

    return (0);
}

int close_window(t_mlx *mymlx)
{
    mlx_destroy_window(mymlx->mlx, mymlx->win);
    exit(0);
}
