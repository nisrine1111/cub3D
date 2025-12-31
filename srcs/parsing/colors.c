/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:30:56 by abouknan          #+#    #+#             */
/*   Updated: 2025/12/31 05:38:53 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_parsing.h"

static int	parse_color_textue(char *line)
{
	int	comma_count;
	int	i;

	if (!line)
		return (0);
	comma_count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma_count++;
		else if (!ft_isdigit(line[i]) && line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (comma_count == 2);
}

static char	*skip_frst_color(t_data *data, char *line, t_color *color)
{
	if (*line == 'C' || *line == 'F')
		line++;
	line = skip_spacess(line);
	if (!parse_color_textue(line))
		print_error_exit(data, "Error\nInvalid color format\n");
	color->r = ft_atoi(line);
	if (color->r < 0 || color->r > 255)
		print_error_exit(data, "Error\nInvalid color format\n");
	return (line);
}

static int	parse_color_to_int(char *line, t_data *data)
{
	t_color	color;

	line = skip_frst_color(data, line, &color);
	while (*line && *line != ',')
		line++;
	line++;
	color.g = ft_atoi(line);
	if (color.g < 0 || color.g > 255)
		print_error_exit(data, "Error\nInvalid color format\n");
	while (*line && *line != ',')
		line++;
	line++;
	color.b = ft_atoi(line);
	if (color.b < 0 || color.b > 255)
		print_error_exit(data, "Error\nInvalid color format\n");
	return (color.r << 16 | color.g << 8 | color.b);
}

void	check_floor(t_data *game, char *color_str)
{
	if (game->floor_color != -1)
		print_error_exit(game, "Error\nDuplicate floor color (F) identifier\n");
	game->floor_color = parse_color_to_int(color_str, game);
}

void	check_ceiling(t_data *game, char *color_str)
{
	if (game->ceiling_color != -1)
		print_error_exit(game,
			"Error\nDuplicate ceiling color (C) identifier\n");
	game->ceiling_color = parse_color_to_int(color_str, game);
}
