#include "../includes/cub3d.h"
#include "mlx.h"

void    mymlx_pixel_put(t_mlx *mymlx, int x, int y, int color){
    char    *dest;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dest = mymlx->addr + (y * mymlx->line_lenght + x * (mymlx->bits_per_pixel / 8));
    *(unsigned int *)dest = color;
}

int main(){
    t_mlx mymlx;

    mymlx.mlx = mlx_init();
    load_texture(&mymlx, &mymlx.north, "./textures/north.xpm");
    load_texture(&mymlx, &mymlx.south, "./textures/south.xpm");
    load_texture(&mymlx, &mymlx.east, "./textures/east.xpm");
    load_texture(&mymlx, &mymlx.west, "./textures/west.xpm");
    load_texture(&mymlx, &mymlx.door, "./textures/door.xpm");
    mymlx.win = mlx_new_window(mymlx.mlx, WIDTH, HEIGHT, "Hello Cub3D");
    mymlx.img = mlx_new_image(mymlx.mlx, WIDTH, HEIGHT);
    mymlx.addr = mlx_get_data_addr(mymlx.img, &mymlx.bits_per_pixel, &mymlx.line_lenght, &mymlx.endian);
    init_map(&mymlx);
    init_player(&mymlx);
    cast_rays(&mymlx);
    render_3d(&mymlx);
    mlx_put_image_to_window(mymlx.mlx, mymlx.win, mymlx.img, 0, 0);
    mlx_hook(mymlx.win, 2, 1L<<0, handle_key, &mymlx);
    mlx_hook(mymlx.win, 17, 0, close_window, &mymlx);
    mlx_loop(mymlx.mlx);
    return(0);
}