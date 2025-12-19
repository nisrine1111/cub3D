#include "../includes/cub3d.h"
#include "mlx.h"

void	mymlx_pixel_put(t_mlx *mymlx, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= mymlx->w_width || y < 0 || y >= mymlx->w_height)
		return ;
	dest = mymlx->addr + (y * mymlx->line_lenght + x * (mymlx->bits_per_pixel
				/ 8));
	*(unsigned int *)dest = color;
}

static void	init_mlx_data(t_mlx *mymlx, t_data *game_data)
{
	mymlx->w_height = game_data->grid_height * TILE;
	mymlx->w_width = game_data->grid_width * TILE;
	mymlx->num_rays = mymlx->w_width;
	mymlx->all_rays.rays = malloc(sizeof(t_ray) * mymlx->num_rays);
	if (!mymlx->all_rays.rays)
		return ;
	mymlx->mlx = mlx_init();
	if (!mymlx->mlx)
		return ;
	mymlx->floor_color = (game_data->floor_rgb[0] << 16)
		| (game_data->floor_rgb[1] << 8) | game_data->floor_rgb[2];
	mymlx->ceiling_color = (game_data->ceiling_rgb[0] << 16)
		| (game_data->ceiling_rgb[1] << 8) | game_data->ceiling_rgb[2];
	mymlx->win = mlx_new_window(mymlx->mlx, mymlx->w_width,
			mymlx->w_height, "Cub3D");
}

static void	load_all_textures(t_mlx *mymlx, t_data *game_data)
{
	load_texture(mymlx, &mymlx->north, game_data->wall_textures.north_path);
	load_texture(mymlx, &mymlx->south, game_data->wall_textures.south_path);
	load_texture(mymlx, &mymlx->east, game_data->wall_textures.east_path);
	load_texture(mymlx, &mymlx->west, game_data->wall_textures.west_path);
	load_texture(mymlx, &mymlx->door, "./textures/door.xpm");
	load_sprites(mymlx);
}

int	main(int ac, char **av)
{
	t_mlx	mymlx;
	t_data	game_data;

	if (ac != 2)
		return (printf("Error\nUsage: ./cub3D <map_file.cub>\n"), 1);
	init_data(&game_data);
	parse_map(&game_data, av[1]);
	init_mlx_data(&mymlx, &game_data);
	if (!mymlx.mlx || !mymlx.win)
		return (gc_free_all(), printf("Error\nMLX init failed\n"), 1);
	init_map(&mymlx, &game_data);
	init_player(&mymlx, &game_data);
	load_all_textures(&mymlx, &game_data);
	mymlx.frame_counter = 0;
	mymlx.mouse_initialized = 0;
	mymlx.mouse_sensitivity = 0.0007;
	mlx_loop_hook(mymlx.mlx, render_frame, &mymlx);
	mlx_hook(mymlx.win, 2, 1L << 0, key_press, &mymlx);
	mlx_hook(mymlx.win, 3, 1L << 1, key_release, &mymlx);
	mlx_hook(mymlx.win, 6, 1L << 6, mouse_move, &mymlx);
	mlx_hook(mymlx.win, 17, 0, close_window, &mymlx);
	mlx_loop(mymlx.mlx);
	gc_free_all();
	return (0);
}
