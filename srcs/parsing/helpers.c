/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 20:31:09 by abouknan          #+#    #+#             */
/*   Updated: 2025/12/11 03:49:13 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_parsing.h"

void	print_error_exit(t_data *game, char *message)
{
	(void)game;
	ft_putstr_fd(message, 2);
	ft_exit(-1);
}

void	init_data(t_data *game)
{
	game->map = NULL;
	game->floor_rgb[0] = -1;
	game->floor_rgb[1] = -1;
	game->floor_rgb[2] = -1;
	game->ceiling_rgb[0] = -1;
	game->ceiling_rgb[1] = -1;
	game->ceiling_rgb[2] = -1;
	game->grid_width = 0;
	game->grid_height = 0;
	game->spawn_x = -1;
	game->spawn_y = -1;
	game->spawn_dir = 0;
	game->wall_textures.north_path = NULL;
	game->wall_textures.south_path = NULL;
	game->wall_textures.west_path = NULL;
	game->wall_textures.east_path = NULL;
}

void	init_parser(t_parser *parser)
{
	parser->fd = -1;
	parser->line = NULL;
	parser->content = gc_strdup("");
	parser->tokens = NULL;
	parser->map_lines = NULL;
}

short	count_array(char **array)
{
	short	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	spawn_player(t_data *game, char **grid)
{
	int	row;
	int	col;

	game->map = grid;
	game->grid_width = 0;
	row = 0;
	while (grid[row])
	{
		if (ft_strlen(grid[row]) > (size_t)game->grid_width)
			game->grid_width = ft_strlen(grid[row]);
		col = 0;
		while (grid[row][col])
		{
			if (is_player(grid[row][col]))
			{
				game->spawn_x = col;
				game->spawn_y = row;
			}
			col++;
		}
		row++;
	}
	game->grid_height = row;
}
