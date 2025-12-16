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

static int	is_door_at_boundary(char **grid, size_t row)
{
	return (row == 0 || !grid[row + 1]);
}

static int	horiz_walls(char **grid, size_t row, size_t col)
{
	return (grid[row][col - 1] == '1' && grid[row][col + 1] == '1');
}

static int	vert_space(char **grid, size_t row, size_t col)
{
	size_t	prev_len;
	size_t	next_len;

	prev_len = ft_strlen(grid[row - 1]);
	next_len = ft_strlen(grid[row + 1]);
	if (prev_len < col || next_len < col)
		return (0);
	if (grid[row - 1][col] != '0' && !is_player(grid[row - 1][col]))
		return (0);
	if (grid[row + 1][col] != '0' && !is_player(grid[row + 1][col]))
		return (0);
	return (1);
}

static int	valid_door(char **grid, size_t row, size_t col)
{
	if (is_door_at_boundary(grid, row))
		return (0);
	if (!horiz_walls(grid, row, col))
		return (0);
	if (!vert_space(grid, row, col))
		return (0);
	return (1);
}

// 2: horizental door -> walls should be on left, right
// 4: verttical door -> walls should be on top, buttom
void	check_doors(t_parser *parser, t_data *game,
			size_t row, size_t col)
{
	char	**grid;

	grid = parser->map_lines;
	row = -1;
	while (grid[++row])
	{
		col = 0;
		while (grid[row][col])
		{
			if (grid[row][col] == 'D')
			{
				if (!valid_door(grid, row, col))
					print_error_exit(game,
						"Error\nInvalid door placement\nDoors must have walls on sides and spaces above/below\n");
			}
			col++;
		}
	}
}
