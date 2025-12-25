#include "../includes/cub3d.h"

static void draw_floor_and_ceiling(t_mlx *m)
{
    int x;
    int y;

    y = 0;
    while (y < m->w_height / 2)
    {
        x = 0;
        while (x < m->w_width)
        {
            mymlx_pixel_put(m, x, y, m->ceiling_color);
            x++;
        }
        y++;    
    }
    y = m->w_height / 2;
    while (y < m->w_height)
    {
        x = 0;
        while (x < m->w_width)
        {
            mymlx_pixel_put(m, x, y, m->floor_color);
            x++;
        } 
        y++;
    }    
}


int render_frame(t_mlx *m)
{
    int i;

    i = 0;
    m->img = mlx_new_image(m->mlx, m->w_width, m->w_height);
    m->addr = mlx_get_data_addr(m->img, &m->bits_per_pixel, &m->line_lenght, &m->endian);
    draw_floor_and_ceiling(m);
    cast_rays(m);
    m->frame_counter++;
    if (m->frame_counter % 10 == 0)
    {
        while (i < m->sprite_count)
        {
            m->sprites[i].frame = (m->sprites[i].frame + 1) % 4;
            i++;
        }  
    }
    render_3d(m);
    render_sprites(m);
    draw_minimap(m);
    draw_minimap_rays(m);
    draw_minimap_player(m);
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    mlx_destroy_image(m->mlx, m->img);
    mlx_mouse_move(m->mlx, m->win, m->w_width/2, m->w_height/2);
    return (0);
}

void render_3d(t_mlx *m)
{
    int col;
    t_ray *ray;
    
    col = 0;
    while (col < m->num_rays)
    {
        ray = &m->all_rays.rays[col];
        draw_textured_wall(m, col, ray);
        col++;
    }
}

void load_sprites(t_mlx *m)
{
    int i;

    i = 0;
    while (i < m->sprite_count)
    {
        load_texture(m, &m->sprites[i].frames[0], "./textures/torch1.xpm");
        load_texture(m, &m->sprites[i].frames[1], "./textures/torch2.xpm");
        load_texture(m, &m->sprites[i].frames[2], "./textures/torch3.xpm");
        load_texture(m, &m->sprites[i].frames[3], "./textures/torch4.xpm");

        m->sprites[i].frame = 0;
        i++;
    }
}
