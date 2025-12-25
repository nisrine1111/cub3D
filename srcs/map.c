#include "../includes/cub3d.h"

void	init_map_size(t_mlx *mlx, t_data *game)
{
	mlx->map_width = game->grid_width;
	mlx->map_height = game->grid_height;
}

void	allocate_map(t_mlx *mlx)
{
	int	y;

	y = 0;
	mlx->map = malloc(sizeof(int *) * mlx->map_height);
	if (!mlx->map)
		exit(1);
	while (y < mlx->map_height)
	{
		mlx->map[y] = malloc(sizeof(int) * mlx->map_width);
		if (!mlx->map[y])
			exit(1);
		y++;
	}
}

static int	get_tile_value(char c, t_data *game)
{
	if (c == '1')
		return (1);
	if (c == '0')
		return (0);
	if (c == '2')
		return (2);
	if (c == '4')
		return (4);
	if (c == '6')
		return (6);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->spawn_dir = &c;
		return (0);
	}
	return (1);
}

void	fill_map(t_mlx *mlx, t_data *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < mlx->map_height)
	{
		x = 0;
		while (x < mlx->map_width)
		{
			mlx->map[y][x] = get_tile_value(game->map[y][x], game);
			x++;
		}
		y++;
	}
}

static int	count_sprites(t_mlx *mlx)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < mlx->map_height)
	{
		x = 0;
		while (x < mlx->map_width)
		{
			if (mlx->map[y][x] == 6)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	init_sprites(t_mlx *mlx)
{
	int	y;
	int	x;
	int	k;

	mlx->sprite_count = count_sprites(mlx);
	mlx->sprites = malloc(sizeof(t_sprite) * mlx->sprite_count);
	if (!mlx->sprites)
		exit(1);
	k = 0;
	y = 0;
	while (y < mlx->map_height)
	{
		x = 0;
		while (x < mlx->map_width)
		{
			if (mlx->map[y][x] == 6)
			{
				mlx->sprites[k].x = x * TILE + TILE / 2;
				mlx->sprites[k].y = y * TILE + TILE / 2;
				mlx->sprites[k].distance = 0;
				k++;
			}
			x++;
		}
		y++;
	}
}

void	init_map(t_mlx *mlx, t_data *game)
{
	init_map_size(mlx, game);
	allocate_map(mlx);
	fill_map(mlx, game);
	init_sprites(mlx);
}

void toggle_door(t_mlx *m)
{
    int mx;
    int my;

    mx = (int)((m->player.x + cos(m->player.dir) * DOOR_DISTANCE) / TILE);
    my = (int)((m->player.y + sin(m->player.dir) * DOOR_DISTANCE) / TILE);
    if (mx < 0 || mx >= m->map_width || my < 0 || my >= m->map_height)
        return;
    if (m->map[my][mx] == 2)
        m->map[my][mx] = 3;
    else if (m->map[my][mx] == 3)
        m->map[my][mx] = 2;
    if (m->map[my][mx] == 4){
        m->map[my][mx] = 5;
    }
    else if (m->map[my][mx] == 5)
        m->map[my][mx] = 4;
}
