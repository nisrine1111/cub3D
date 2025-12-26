/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:18:24 by nachabi-          #+#    #+#             */
/*   Updated: 2025/12/26 15:26:22 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	int (x), (y), (k);
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
