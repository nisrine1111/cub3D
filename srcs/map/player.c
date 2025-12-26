/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:56:07 by nachabi-          #+#    #+#             */
/*   Updated: 2025/12/26 16:04:10 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player(t_mlx *mlx, t_data *game)
{
	char	*c;

	mlx->player.x = game->spawn_x * TILE + TILE / 2;
	mlx->player.y = game->spawn_y * TILE + TILE / 2;
	c = game->spawn_dir;
	if (*c == 'N')
		mlx->player.dir = M_PI * 1.5;
	else if (*c == 'S')
		mlx->player.dir = M_PI / 2;
	else if (*c == 'W')
		mlx->player.dir = M_PI;
	else if (*c == 'E')
		mlx->player.dir = 0;
}

void	update_player_movement(t_mlx *mymlx)
{
	float (move_step), (move_x), (move_y), (strafe_step)
		, (strafe_x), (strafe_y), (next_x), (next_y);
	mymlx->player.dir += mymlx->player.turn_dir * ROT_SPEED;
	mymlx->player.dir = normalize_angle(mymlx->player.dir);
	move_step = mymlx->player.move_dir * MOVE_SPEED;
	move_x = cos(mymlx->player.dir) * move_step;
	move_y = sin(mymlx->player.dir) * move_step;
	strafe_step = mymlx->player.strafe_dir * MOVE_SPEED;
	strafe_x = cos(mymlx->player.dir + M_PI / 2) * strafe_step;
	strafe_y = sin(mymlx->player.dir + M_PI / 2) * strafe_step;
	next_x = mymlx->player.x + move_x + strafe_x;
	next_y = mymlx->player.y + move_y + strafe_y;
	if (can_move(mymlx, next_x, mymlx->player.y))
		mymlx->player.x = next_x;
	if (can_move(mymlx, mymlx->player.x, next_y))
		mymlx->player.y = next_y;
}
