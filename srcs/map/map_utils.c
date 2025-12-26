/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:26:50 by nachabi-          #+#    #+#             */
/*   Updated: 2025/12/26 15:26:53 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	toggle_door(t_mlx *m)
{
	int	mx;
	int	my;

	mx = (int)((m->player.x + cos(m->player.dir) * DOOR_DISTANCE) / TILE);
	my = (int)((m->player.y + sin(m->player.dir) * DOOR_DISTANCE) / TILE);
	if (mx < 0 || mx >= m->map_width || my < 0 || my >= m->map_height)
		return ;
	if (m->map[my][mx] == 2)
		m->map[my][mx] = 3;
	else if (m->map[my][mx] == 3)
		m->map[my][mx] = 2;
	if (m->map[my][mx] == 4)
		m->map[my][mx] = 5;
	else if (m->map[my][mx] == 5)
		m->map[my][mx] = 4;
}
