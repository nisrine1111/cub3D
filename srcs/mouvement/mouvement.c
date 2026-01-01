/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:42:10 by nachabi-          #+#    #+#             */
/*   Updated: 2025/12/26 15:53:10 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	key_press_helper(t_mlx *mymlx)
{
	mymlx->mouse_enabled = !mymlx->mouse_enabled;
	if (mymlx->mouse_enabled)
	{
		mlx_mouse_hide(mymlx->mlx, mymlx->win);
		mlx_mouse_move(mymlx->mlx, mymlx->win,
			mymlx->w_width / 2, mymlx->w_height / 2);
	}
	else
		mlx_mouse_show(mymlx->mlx, mymlx->win);
}

int	key_press(int keycode, t_mlx *mymlx)
{
	mymlx->player.turn_dir = 0;
	mymlx->player.move_dir = 0;
	mymlx->player.strafe_dir = 0;
	if (keycode == KEY_W)
		mymlx->player.move_dir = 1;
	else if (keycode == KEY_S)
		mymlx->player.move_dir = -1;
	if (keycode == KEY_A)
		mymlx->player.strafe_dir = -1;
	else if (keycode == KEY_D)
		mymlx->player.strafe_dir = 1;
	if (keycode == KEY_LEFT)
		mymlx->player.turn_dir = -1;
	else if (keycode == KEY_RIGHT)
		mymlx->player.turn_dir = 1;
	if (keycode == KEY_E)
		toggle_door(mymlx);
	if (keycode == KEY_M)
		key_press_helper(mymlx);
	if (keycode == KEY_ESC)
		close_window(mymlx);
	update_player_movement(mymlx);
	return (0);
}

int	key_release(int key, t_mlx *m)
{
	if (key == KEY_W || key == KEY_S)
		m->player.move_dir = 0;
	if (key == KEY_A || key == KEY_D)
		m->player.strafe_dir = 0;
	if (key == KEY_LEFT || key == KEY_RIGHT)
		m->player.turn_dir = 0;
	return (0);
}

int	mouse_move(int x, int y, t_mlx *m)
{
	int	center_x;
	int	dx;

	(void)y;
	if (!m->mouse_enabled)
		return (0);
	center_x = m->w_width / 2;
	dx = x - center_x;
	if (dx != 0)
	{
		m->player.dir += dx * m->mouse_sensitivity;
		m->player.dir = normalize_angle(m->player.dir);
	}
	mlx_mouse_move(m->mlx, m->win,
		center_x, m->w_height / 2);
	return (0);
}

int	close_window(t_mlx *mymlx)
{
	free_map(mymlx);
	free_mlx(mymlx);
	exit(0);
}
