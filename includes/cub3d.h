#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define TILE 128
# define MAP_W 8
# define MAP_H 8
# define WIDTH (MAP_W * TILE)
# define HEIGHT (MAP_H * TILE)
# define FOV (M_PI / 3)
# define MOVE_SPEED 5
# define ROT_SPEED 0.1
# define PLAYER_RADIUS 5
# define NUM_RAYS WIDTH
# define TEX_W 128
# define TEX_H 128
# define MMAP_SCALE 0.2
# define DOOR_DISTANCE 100

# define RED    0xFF0000
# define GREY   0x808080
# define YELLOW 0xFFFF00

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define KEY_E 101


typedef struct s_player{
    double  x;
    double  y;
    double  dir;
    int     turn_dir;
    int     move_dir;
    int     strafe_dir;
    int     move_step;
}   t_player;

typedef struct s_ray
{
    double  ray_angle;
    double  distance;
    double  hit_x;
    double  hit_y;
    double  v_x;
    double  v_y;
    double  h_x;
    double  h_y;
    double  wall_x;
    int     hit_side;
    int     tile_type;
    int     h_door;
    int     v_door;
    int     hit_door;

}   t_ray;

typedef struct s_rays
{
    t_ray   rays[NUM_RAYS];
}   t_rays;

typedef struct s_tex
{
    void    *img;
    int     *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
}   t_tex;

typedef struct s_sprites
{
    double  sprite;
    
}   t_sprites;


typedef struct s_mlx{
    void        *mlx;
    void        *win;
    void        *img;
    void        *addr;
    int         map[MAP_H][MAP_W];
    int         bits_per_pixel;
    int         line_lenght;
    int         endian;
    int         floor_color;
    int         ceiling_color;
    t_player    player;
    t_rays      all_rays;
    t_tex       north;
    t_tex       south;
    t_tex       east;
    t_tex       west;
    t_tex       door;
}   t_mlx;


void    mymlx_pixel_put(t_mlx *mymlx, int x, int y, int color);
void    init_map(t_mlx *mymlx);
void    init_player(t_mlx *mymlx);
int     handle_key(int keycode, t_mlx *mymlx);
int     close_window(t_mlx *mymlx);
void    update_player_movement(t_mlx *mymlx);
int     is_wall(t_mlx *m, float x, float y);
int     can_move(t_mlx *m, float nx, float ny);
void    cast_single_ray(t_mlx *mymlx, t_ray *ray);
void    cast_rays(t_mlx *mymlx);
double  normalize_angle(double angle);
double  get_horizontal_hit(t_mlx *m, t_ray *ray);
double  get_vertical_hit(t_mlx *m, t_ray *ray);
void    render_frame(t_mlx *m);
void    draw_textured_wall(t_mlx *m, int col, t_ray *ray);
void    render_3d(t_mlx *m);
void    load_texture(t_mlx *m, t_tex *tex, char *path);
t_tex   *select_texture(t_mlx *m, t_ray *ray);
void    draw_minimap(t_mlx *m);
void    draw_minimap_player(t_mlx *m);
void    draw_minimap_rays(t_mlx *m);
void    toggle_door(t_mlx *m);


#endif