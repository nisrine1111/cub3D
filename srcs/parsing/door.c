/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                 			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:31:01 by abouknan          #+#    #+#             */
/*   Updated: 2025/12/11 02:30:54 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_parsing.h"

static int	is_horizontal_door(char **grid, size_t row, size_t col)
{
	size_t	prev_len;
	size_t	next_len;

	if (col == 0 || !grid[row][col + 1])
		return (0);
	if (grid[row][col - 1] != '1' || grid[row][col + 1] != '1')
		return (0);
	if (row == 0 || !grid[row + 1])
		return (0);
	prev_len = ft_strlen(grid[row - 1]);
	next_len = ft_strlen(grid[row + 1]);
	if (prev_len <= col || next_len <= col)
		return (0);
	if (grid[row - 1][col] == '1' && grid[row + 1][col] == '1')
		return (0);
	return (1);
}

static int	is_vertical_door(char **grid, size_t row, size_t col)
{
	size_t	prev_len;
	size_t	next_len;

	if (row == 0 || !grid[row + 1])
		return (0);
	prev_len = ft_strlen(grid[row - 1]);
	next_len = ft_strlen(grid[row + 1]);
	if (prev_len <= col || next_len <= col)
		return (0);
	if (grid[row - 1][col] != '1' || grid[row + 1][col] != '1')
		return (0);
	if (col == 0 || !grid[row][col + 1])
		return (0);
	if (grid[row][col - 1] == '1' && grid[row][col + 1] == '1')
		return (0);
	return (1);
}

void	check_doors(t_parser *parser, t_data *game, int p)
{
	char	**grid;
	size_t	row;
	size_t	col;

	if (p != 1)
		print_error_exit(game, "Error\nOne player required\n");
	grid = parser->map_lines;
	row = 0;
	while (grid[row])
	{
		col = 0;
		while (grid[row][col])
		{
			if (grid[row][col] == '2' && !is_horizontal_door(grid, row, col))
				print_error_exit(game, "Error\nInvalid door placement\n");
			if (grid[row][col] == '4' && !is_vertical_door(grid, row, col))
				print_error_exit(game, "Error\nInvalid door placement\n");
			col++;
		}
		row++;
	}
}
