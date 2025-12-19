/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:31:15 by abouknan          #+#    #+#             */
/*   Updated: 2025/12/11 03:56:22 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_parsing.h"

static void	check_extension(char *filepath, t_data *game)
{
	size_t	len;

	len = ft_strlen(filepath);
	if (len < 5 || ft_strncmp(&filepath[len - 4], ".cub", 4) != 0)
		print_error_exit(game,
			"Error\nInvalid file extension\nExpected: .cub\n");
}

static void	check_fd(t_parser *parser, char *filepath, t_data *game)
{
	parser->fd = open(filepath, O_RDONLY);
	if (parser->fd == -1)
		print_error_exit(game,
			"Error\nCannot open file\nCheck file path and permissions\n");
}

static void	create_map(t_parser *parser, t_data *game)
{
	read_map(parser, game);
	if (!parser->content || !parser->content[0])
		print_error_exit(game, "Error\nEmpty or invalid map file\n");
	parser->map_lines = gc_split(parser->content, '\n');
	if (!parser->map_lines)
		print_error_exit(game, "Error\nFailed to parse map content\n");
	clean_map_lines(parser->map_lines);
}

void	parse_map(t_data *game, char *filepath)
{
	t_parser	parser;

	init_parser(&parser);
	check_extension(filepath, game);
	check_fd(&parser, filepath, game);
	create_map(&parser, game);
	spawn_player(game, parser.map_lines);
	validate_walls_and_borders(&parser, game);
}
