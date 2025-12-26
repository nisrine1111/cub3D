/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:12:30 by nachabi-          #+#    #+#             */
/*   Updated: 2025/12/26 16:42:53 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	normalize_angle(double angle)
{
	double	two_pi;

	two_pi = 2 * M_PI;
	angle = fmod(angle, two_pi);
	if (angle <= 0)
		angle += two_pi;
	return (angle);
}

void	cast_rays(t_mlx *mymlx)
{
	double	ray_angle;
	double	angle_step;
	int		col;

	angle_step = FOV / mymlx->num_rays;
	col = 0;
	ray_angle = mymlx->player.dir - (FOV / 2);
	while (col < mymlx->num_rays)
	{
		ray_angle = normalize_angle(ray_angle);
		mymlx->all_rays.rays[col].ray_angle = ray_angle;
		cast_single_ray(mymlx, &mymlx->all_rays.rays[col]);
		ray_angle += angle_step;
		col++;
	}
}
