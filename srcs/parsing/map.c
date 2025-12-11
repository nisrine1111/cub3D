/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:31:04 by abouknan          #+#    #+#             */
/*   Updated: 2025/12/11 03:52:49 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_parsing.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	clean_map_lines(char **lines)
{
	int	i;
	int	len;

	if (!lines)
		return ;
	i = -1;
	while (lines[++i])
	{
		len = ft_strlen(lines[i]);
		if (len > 0 && lines[i][len - 1] == '\n')
			lines[i][len - 1] = '\0';
	}
}

void	validate_walls_and_borders(t_parser *parser, t_data *game)
{
	char	**g;
	int		r;
	int		c;
	int		p;

	g = parser->map_lines;
	if (!g || !g[0])
		print_error_exit(game, "Error\nInvalid map grid\n");
	r = -1;
	while (g[0][++r])
		if (g[0][r] != '1' && g[0][r] != ' ')
			print_error_exit(game, "Error\nInvalid top border\n");
	r = -1;
	p = 0;
	while (g[++r])
	{
		c = -1;
		while (g[r][++c])
		{
			if (is_player(g[r][c]) && ++p)
				if (r > 0 && r < game->grid_height - 1 && (g[r - 1][c] == ' '
					|| g[r + 1][c] == ' ' || g[r][c + 1] == ' ' || g[r][c - 1] == ' '))
					print_error_exit(game, "Error\nMap not closed\n");
			if ((g[r][c] == '0') && r > 0 && r < game->grid_height - 1
				&& (g[r - 1][c] == ' ' || g[r + 1][c] == ' '
					|| g[r][c + 1] == ' ' || g[r][c - 1] == ' '))
				print_error_exit(game, "Error\nMap not closed\n");
		}
	}
	if (p != 1)
		print_error_exit(game, "Error\nOne player required\n");
	check_doors(parser, game, -1, -1);
}

void	parse_entry(t_parser *parser, t_data *game)
{
	if (!parser->line)
		print_error_exit(game, "Error\nInvalid configuration line\n");
	parser->tokens = gc_split(parser->line, ' ');
	if (!parser->tokens || count_array(parser->tokens) != 2)
		print_error_exit(game, "Error\nInvalid config format\n");
	if (!ft_strncmp(parser->tokens[0], "NO", 2)
		|| !ft_strncmp(parser->tokens[0], "SO", 2)
		|| !ft_strncmp(parser->tokens[0], "WE", 2)
		|| !ft_strncmp(parser->tokens[0], "EA", 2))
		check_texture(parser, game, parser->tokens[0]);
	else if (!ft_strncmp(parser->tokens[0], "F", 1))
		check_floor(game, parser->tokens[1]);
	else if (!ft_strncmp(parser->tokens[0], "C", 1))
		check_ceiling(game, parser->tokens[1]);
	else
		print_error_exit(game, "Error\nUnknown identifier\n");
}

void	read_map(t_parser *parser, t_data *game)
{
	int	lc;
	int	hm;

	lc = 0;
	hm = 0;
	while (1)
	{
		parser->line = get_next_line(parser->fd);
		if (!parser->line)
			break ;
		if (lc < 6)
			parser->line = gc_strtrim(parser->line, " \t\n\v\f\r");
		if (!parser->line || !parser->line[0])
			continue ;
		if (parser->line[0] == '\n' && hm)
			print_error_exit(game, "Error\nEmpty line in map\n");
		if (parser->line[0] != '\n' && ++lc)
		{
			if (lc <= 6)
				parse_entry(parser, game);
			else if (hm++ || 1)
				parser->content = gc_strjoin(parser->content, parser->line);
		}
	}
}
