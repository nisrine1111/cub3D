/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 15:38:59 by nachabi-          #+#    #+#             */
/*   Updated: 2026/01/01 15:40:26 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(t_mlx *mlx)
{
	int	y;

	y = 0;
	while (y < mlx->map_height)
	{
		free(mlx->map[y]);
		y++;
	}
	free(mlx->map);
}

void	free_mlx(t_mlx *mlx)
{
	free(mlx->all_rays.rays);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

void	free_sprites(t_mlx *mlx)
{
	if (mlx->sprites)
	{
		free(mlx->sprites);
		mlx->sprites = NULL;
	}
}

void	hundle_sprites(t_mlx *mlx)
{
	if (!mlx->sprites)
	{
		free_map(mlx);
		free_mlx(mlx);
		exit(1);
	}
}
