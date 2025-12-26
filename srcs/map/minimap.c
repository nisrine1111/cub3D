/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:30:38 by nachabi-          #+#    #+#             */
/*   Updated: 2025/12/26 15:34:55 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_minimap_tile(t_mlx *m, int x, int y)
{
	int (color), (sx), (sy), (i), (j);
	color = 0xAAAAAA;
	if (m->map[y][x] == 1)
		color = 0x222222;
	sx = x * TILE * MMAP_SCALE;
	sy = y * TILE * MMAP_SCALE;
	i = 0;
	while (i < TILE * MMAP_SCALE)
	{
		j = 0;
		while (j < TILE * MMAP_SCALE)
		{
			mymlx_pixel_put(m, sx + j, sy + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_mlx *m)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->map_height)
	{
		x = 0;
		while (x < m->map_width)
		{
			draw_minimap_tile(m, x, y);
			x++;
		}
		y++;
	}
}

void	draw_minimap_player(t_mlx *m)
{
	int	px;
	int	py;
	int	x;
	int	y;

	px = m->player.x * MMAP_SCALE;
	py = m->player.y * MMAP_SCALE;
	y = -3;
	while (y <= 3)
	{
		x = -3;
		while (x <= 3)
		{
			mymlx_pixel_put(m, px + x, py + y, 0xFF0000);
			x++;
		}
		y++;
	}
}

static void	draw_one_minimap_ray(t_mlx *m, int px, int py, int col)
{
	int (rx), (ry), (dx), (dy), (steps), (i);
	float (x_inc), (y_inc), (xx), (yy);
	rx = m->all_rays.rays[col].hit_x * MMAP_SCALE;
	ry = m->all_rays.rays[col].hit_y * MMAP_SCALE;
	dx = rx - px;
	dy = ry - py;
	steps = abs(dx);
	if (abs(dy) > steps)
		steps = abs(dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	xx = px;
	yy = py;
	i = 0;
	while (i < steps)
	{
		mymlx_pixel_put(m, xx, yy, 0x00FF00);
		xx += x_inc;
		yy += y_inc;
		i++;
	}
}

void	draw_minimap_rays(t_mlx *m)
{
	int	px;
	int	py;
	int	col;

	px = m->player.x * MMAP_SCALE;
	py = m->player.y * MMAP_SCALE;
	col = 0;
	while (col < m->num_rays)
	{
		draw_one_minimap_ray(m, px, py, col);
		col++;
	}
}
