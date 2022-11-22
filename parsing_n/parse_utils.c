/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:38:38 by nboratko          #+#    #+#             */
/*   Updated: 2022/11/16 14:07:37 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	are_walls_around(char **map, int i, int k, int height)
{
	if (map[i][k] == ' ')
	{
		if (!find_a_wall(map, i, k, height))
			return (0);
	}
	return (1);
}

int	is_contour(t_game *game, char **map, int i, int k)
{
	if (i == 0 || i == game->height - 1)
		return (1);
	if (k == 0 || k == game->width - 1)
		return (2);
	if (map[i][k + 1] == '\0' || (map[i][k + 1] && map[i][k + 1] == '\n'))
		return (3);
	return (0);
}

int	check_wall(t_game *game, int i, int k)
{
	if (!is_contour(game, game->map, i, k) && game->map[i][k] == ' ')
	{
		if (!are_walls_around(game->map, i, k, game->height - 1))
			return (printf("Error\nInvalid wall\n"), 0);
	}	
	return (1);
}

void	get_coords(t_game *game, char **map, int i, int k)
{
	if (map[i][k] == 'N')
		game->start = 'N';
	else if (map[i][k] == 'S')
		game->start = 'S';
	else if (map[i][k] == 'W')
		game->start = 'W';
	else if (map[i][k] == 'E')
		game->start = 'E';
}

int	valid_walls_2(t_game *game, char **map, int i)
{
	int	k;
	int	enter;

	enter = 0;
	k = -1;
	while (map[i][++k])
	{
		if (!check_contour_t(map, i))
			return (printf("Error\nInvalid wall\n"), 0);
		if (map[i][k] == 'N' || map[i][k] == 'W' || map[i][k] == 'E'
			|| map[i][k] == 'S')
			get_coords(game, map, i, k);
		if ((i == 0 || i == game->height) && !(map[i][k] == ' '
			|| map[i][k] == '1' || map[i][k] == 10))
			return (0);
		if (map[i][k] == '1' && i != 0)
			enter = 1;
		if (enter && !check_wall(game, i, k))
			return (0);
	}
	return (1);
}
