/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:30:56 by abouknan          #+#    #+#             */
/*   Updated: 2025/12/11 03:52:49 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_parsing.h"

static int	valid_colors(const char *str)
{
	char	**colors;
	char	*trimmed;
	int		i;
	int		j;

	colors = gc_split(str, ',');
	if (!colors)
		return (0);
	i = -1;
	while (colors[++i])
	{
		if (i > 2)
			return (0);
		trimmed = gc_strtrim(colors[i], " \t\n\v\f\r");
		if (!trimmed || !trimmed[0])
			return (0);
		j = -1;
		while (trimmed[++j])
			if (!ft_isdigit(trimmed[j]))
				return (0);
		if (ft_atoi(trimmed) < 0 || ft_atoi(trimmed) > 255)
			return (0);
	}
	return (i == 3);
}

static void	parse_rgb(const char *str, int *rgb)
{
	char	**colors;
	char	*trimmed;
	int		i;

	colors = gc_split(str, ',');
	i = 0;
	while (i < 3 && colors[i])
	{
		trimmed = gc_strtrim(colors[i], " \t\n\v\f\r");
		rgb[i] = ft_atoi(trimmed);
		i++;
	}
}

void	check_floor(t_data *game, char *color_str)
{
	if (game->floor_rgb[0] != -1)
		print_error_exit(game, "Error\nDuplicate floor color (F) identifier\n");
	if (!valid_colors(color_str))
		print_error_exit(game,
			"Error\nInvalid floor color format\nExpected: F R,G,B (0-255)\n");
	parse_rgb(color_str, game->floor_rgb);
}

void	check_ceiling(t_data *game, char *color_str)
{
	if (game->ceiling_rgb[0] != -1)
		print_error_exit(game,
			"Error\nDuplicate ceiling color (C) identifier\n");
	if (!valid_colors(color_str))
		print_error_exit(game,
			"Error\nInvalid ceiling color format\nExpected: C R,G,B (0-255)\n");
	parse_rgb(color_str, game->ceiling_rgb);
}
