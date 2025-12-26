/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:29:41 by nachabi-          #+#    #+#             */
/*   Updated: 2025/12/26 16:39:57 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_texture(t_mlx *m, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(m->mlx,
			path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error loading texture: %s\n", path);
		exit(1);
	}
	tex->addr = (int *)mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
}

t_tex	*select_texture(t_mlx *m, t_ray *ray)
{
	double	ang;

	ang = ray->ray_angle;
	if (ray->hit_door == 1)
		return (&m->door);
	if (ray->hit_side == 1)
	{
		if (ang > M_PI_2 && ang < 3 * M_PI_2)
			return (&m->west);
		else
			return (&m->east);
	}
	else
	{
		if (ang > 0 && ang < M_PI)
			return (&m->south);
		else
			return (&m->north);
	}
}

void	draw_textured_wall(t_mlx *m, int col, t_ray *ray)
{
	double (dist), (wall_h), (step), (tex_pos);
	int (y), (start), (end), (tex_x), (tex_y), (color);
	t_tex (*tex);
	dist = ray->distance * cos(ray->ray_angle - m->player.dir);
	wall_h = (TILE / dist) * (m->w_width / 2) / tan(FOV / 2);
	start = m->w_height / 2 - wall_h / 2;
	end = m->w_height / 2 + wall_h / 2;
	tex = select_texture(m, ray);
	tex_x = ray->wall_x * tex->width;
	step = (double)tex->height / (end - start);
	tex_pos = 0;
	y = start;
	while (y < end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = tex->addr[tex_y * tex->width + tex_x];
		mymlx_pixel_put(m, col, y, color);
		y++;
	}
}
