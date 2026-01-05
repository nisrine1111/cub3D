/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 15:38:59 by nachabi-          #+#    #+#             */
/*   Updated: 2026/01/05 20:45:33 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	destroy_textures(t_mlx *mlx)
{
	if (mlx->north.img)
		mlx_destroy_image(mlx->mlx, mlx->north.img);
	if (mlx->south.img)
		mlx_destroy_image(mlx->mlx, mlx->south.img);
	if (mlx->east.img)
		mlx_destroy_image(mlx->mlx, mlx->east.img);
	if (mlx->west.img)
		mlx_destroy_image(mlx->mlx, mlx->west.img);
	if (mlx->door.img)
		mlx_destroy_image(mlx->mlx, mlx->door.img);
}

static void	destroy_sprite_frames(t_mlx *mlx)
{
	int	i;
	int	j;

	if (!mlx->sprites)
		return ;
	i = 0;
	while (i < mlx->sprite_count)
	{
		j = 0;
		while (j < 8)
		{
			if (mlx->sprites[i].frames[j].img)
				mlx_destroy_image(mlx->mlx, mlx->sprites[i].frames[j].img);
			j++;
		}
		i++;
	}
}

void	cleanup_and_exit(t_mlx *mlx, int exit_code)
{
	destroy_textures(mlx);
	destroy_sprite_frames(mlx);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	gc_free_all();
	exit(exit_code);
}
