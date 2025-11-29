#include "../includes/cub3d.h"

void load_texture(t_mlx *m, t_tex *tex, char *path)
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

t_tex *select_texture(t_mlx *m, t_ray *ray)
{
    double ang = ray->ray_angle;

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

void draw_textured_wall(t_mlx *m, int col, t_ray *ray)
{
    double  dist = ray->distance * cos(ray->ray_angle - m->player.dir);
    double  wall_h = (TILE / dist) * (WIDTH / 2) / tan(FOV / 2);
    int     y;

    int start = HEIGHT / 2 - wall_h / 2;
    int end = HEIGHT / 2 + wall_h / 2;

    t_tex *tex = select_texture(m, ray);

    int tex_x = ray->wall_x * tex->width;

    double step = (double)tex->height / (end - start);
    double tex_pos = 0;
    y = start;
    while (y < end)
    {
        int tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;
        int color = tex->addr[tex_y * tex->width + tex_x];
        mymlx_pixel_put(m, col, y, color);
        y++;
    }
}

