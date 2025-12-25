/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 00:10:00 by abouknan          #+#    #+#             */
/*   Updated: 2025/12/26 00:05:05 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_parsing.h"

bool	check_wall(t_data *data, int lne, int i, int j)
{
	if (i == 0 || j == 0 || i == data->grid_height - 1 || j == lne - 1)
		return (true);
	return (false);
}

bool	check_out(char **map, int i, int j)
{
	if ((map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S'
			|| map[i][j] == 'N' || map[i][j] == '0') && (map[i][j - 1] == ' '
			|| map[i][j + 1] == ' ' || map[i + 1][j] == ' ' || map[i
			- 1][j] == ' '))
		return (true);
	return (false);
}

void	check_valid_character(char c, t_data *data)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != '2' && c != '4')
	{
		printf("Error\nInvalid character in map\n");
		print_error_exit(data, NULL);
	}
}

void	check_map_valid(char **map, t_data *data, int i, int j)
{
	if (check_wall(data, ft_strlen(map[i]), i, j))
	{
		if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\t')
		{
			printf("Error\nMap is not closed\n");
			print_error_exit(data, NULL);
		}
	}
	if (check_out(map, i, j))
	{
		printf("Error\nMap is not closed\n");
		print_error_exit(data, NULL);
	}
	if (map[i][j] != ' ')
		check_valid_character(map[i][j], data);
}
