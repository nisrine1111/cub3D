/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:31:04 by abouknan          #+#    #+#             */
/*   Updated: 2025/12/27 20:32:23 by abouknan         ###   ########.fr       */
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
	p = 0;
	while (g[++r])
	{
		c = -1;
		while (g[r][++c])
		{
			if (is_player(g[r][c]))
				p++;
			check_map_valid(g, game, r, c);
		}
	}
	check_doors(parser, game, p);
}

void	parse_entry(t_parser *parser, t_data *game)
{
	char	*line_ptr;

	if (!parser->line)
		print_error_exit(game, "Error\nInvalid configuration line\n");
	line_ptr = parser->line;
	while (*line_ptr && (*line_ptr == ' ' || *line_ptr == '\t'))
		line_ptr++;
	if (!ft_strncmp(line_ptr, "NO ", 3) || !ft_strncmp(line_ptr, "SO ", 3)
		|| !ft_strncmp(line_ptr, "WE ", 3) || !ft_strncmp(line_ptr, "EA ", 3))
	{
		parser->tokens = gc_split(parser->line, ' ');
		if (!parser->tokens || count_array(parser->tokens) != 2)
			print_error_exit(game, "Error\nInvalid config format\n");
		check_texture(parser, game, parser->tokens[0]);
	}
	else if (!ft_strncmp(line_ptr, "F ", 2))
		check_floor(game, line_ptr);
	else if (!ft_strncmp(line_ptr, "C ", 2))
		check_ceiling(game, line_ptr);
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
