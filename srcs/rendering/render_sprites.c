/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:49:52 by nachabi-          #+#    #+#             */
/*   Updated: 2025/12/26 17:10:54 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	sort_sprites(t_mlx *m)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < m->sprite_count - 1)
	{
		j = i + 1;
		while (j < m->sprite_count)
		{
			if (m->sprites[i].distance < m->sprites[j].distance)
			{
				tmp = m->sprites[i];
				m->sprites[i] = m->sprites[j];
				m->sprites[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	init_sprite_draw(t_mlx *m, t_sprite *sp, t_sprite_draw *d)
{
	double	dx;
	double	dy;

	dx = sp->x - m->player.x;
	dy = sp->y - m->player.y;
	d->dist = sqrt(dx * dx + dy * dy);
	sp->distance = d->dist;
	d->angle = atan2(dy, dx) - m->player.dir;
	while (d->angle > M_PI)
	{
		d->angle -= 2 * M_PI;
	}
	while (d->angle < -M_PI)
	{
		d->angle += 2 * M_PI;
	}
	if (fabs(d->angle) > FOV / 2)
		return (0);
	d->size = (TILE / d->dist)
		* (m->w_width / 2) / tan(FOV / 2);
	d->screen_x = (m->w_width / 2)
		* (1 + tan(d->angle) / tan(FOV / 2));
	d->start_y = m->w_height / 2 - d->size / 2;
	d->end_y = m->w_height / 2 + d->size / 2;
	return (1);
}

static void	draw_sprite_pixels(t_mlx *m, t_sprite *sp, t_sprite_draw *d)
{
	int (x), (y), (sx), (color), (tex_x), (tex_y);
	t_tex (*tex);
	tex = &sp->frames[sp->frame];
	x = 0;
	while (x < d->size)
	{
		sx = d->screen_x - d->size / 2 + x;
		if (sx >= 0 && sx < m->w_width
			&& m->all_rays.rays[sx].distance >= d->dist)
		{
			tex_x = (int)(x * tex->width / d->size);
			y = d->start_y;
			while (y < d->end_y)
			{
				tex_y = (int)((y - d->start_y) * tex->height / d->size);
				color = tex->addr[tex_y * tex->width + tex_x];
				if (y >= 0 && y < m->w_height && (color & 0x00FFFFFF))
					mymlx_pixel_put(m, sx, y, color);
				y++;
			}
		}
		x++;
	}
}

void	draw_sprite(t_mlx *m, t_sprite *sp)
{
	t_sprite_draw	d;

	if (!init_sprite_draw(m, sp, &d))
		return ;
	draw_sprite_pixels(m, sp, &d);
}

void	render_sprites(t_mlx *m)
{
	int		i;
	int		j;
	double	dx;
	double	dy;

	i = 0;
	j = 0;
	while (i < m->sprite_count)
	{
		dx = m->sprites[i].x - m->player.x;
		dy = m->sprites[i].y - m->player.y;
		m->sprites[i].distance = sqrt(dx * dx + dy * dy);
		i++;
	}
	sort_sprites(m);
	while (j < m->sprite_count)
	{
		draw_sprite(m, &m->sprites[j]);
		j++;
	}
}
