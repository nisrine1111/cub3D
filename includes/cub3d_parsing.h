/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:04:26 by abouknan          #+#    #+#             */
/*   Updated: 2025/12/11 04:54:17 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

# include "../helpers/GarbageCollector/malloc.h"
# include "../helpers/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char				*get_next_line(int fd);

typedef struct s_wall_textures
{
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
}					t_wall_textures;

typedef struct s_data
{
	char			**map;
	int				floor_rgb[3];
	int				ceiling_rgb[3];
	int				grid_width;
	int				grid_height;
	double			spawn_x;
	double			spawn_y;
	char			*spawn_dir;
	t_wall_textures	wall_textures;
}					t_data;

typedef struct s_parser
{
	int				fd;
	char			*line;
	char			*content;
	char			**tokens;
	char			**map_lines;
}					t_parser;

void				init_data(t_data *state);
void				init_parser(t_parser *parser);
void				parse_map(t_data *game, char *filepath);

void				parse_entry(t_parser *parser, t_data *game);
void				read_map(t_parser *parser, t_data *game);

short				count_array(char **array);
void				clean_map_lines(char **map_lines);

void				check_floor(t_data *game, char *color_str);
void				check_ceiling(t_data *game, char *color_str);

void				check_texture(t_parser *parser, t_data *game,
						char *direction);

void				validate_walls_and_borders(t_parser *parser, t_data *game);
int					is_player(char c);

void				check_doors(t_parser *parser, t_data *game, int p);

void				spawn_player(t_data *game, char **grid);

void				print_error_exit(t_data *game, char *message);

#endif
