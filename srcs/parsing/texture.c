/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:31:07 by abouknan          #+#    #+#             */
/*   Updated: 2025/12/11 03:56:28 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_parsing.h"

static int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	check_texture(t_parser *parser, t_data *game, char *direction)
{
	char	**path;

	path = NULL;
	if (!ft_strncmp(direction, "NO", 2))
		path = &game->wall_textures.north_path;
	else if (!ft_strncmp(direction, "SO", 2))
		path = &game->wall_textures.south_path;
	else if (!ft_strncmp(direction, "WE", 2))
		path = &game->wall_textures.west_path;
	else if (!ft_strncmp(direction, "EA", 2))
		path = &game->wall_textures.east_path;
	if (!path)
		print_error_exit(game, "Error\nInvalid texture direction\n");
	if (*path)
		print_error_exit(game, "Error\nDuplicate texture identifier\n");
	if (count_array(parser->tokens) != 2
		|| ft_strncmp(parser->tokens[0], direction, 2))
		print_error_exit(game, "Error\nInvalid texture format\n");
	if (!file_exists(parser->tokens[1]))
		print_error_exit(game, "Error\nTexture file not found\n");
	*path = parser->tokens[1];
}
