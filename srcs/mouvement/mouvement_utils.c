/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:53:22 by nachabi-          #+#    #+#             */
/*   Updated: 2025/12/26 15:54:23 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_wall(t_mlx *m, float x, float y)
{
	int	map_x;
	int	map_y;
	int	tile;

	map_x = (int)(x / TILE);
	map_y = (int)(y / TILE);
	if (map_x < 0 || map_x >= m->map_width
		|| map_y < 0 || map_y >= m->map_height)
		return (1);
	tile = m->map[map_y][map_x];
	if (tile == 1 || tile == 2 || tile == 4)
		return (1);
	return (0);
}

int	can_move(t_mlx *m, float nx, float ny)
{
	float	r;

	r = PLAYER_RADIUS;
	if (is_wall(m, nx + r, ny + r))
		return (0);
	if (is_wall(m, nx - r, ny - r))
		return (0);
	if (is_wall(m, nx + r, ny - r))
		return (0);
	if (is_wall(m, nx - r, ny + r))
		return (0);
	return (1);
}
