/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:40:32 by nboratko          #+#    #+#             */
/*   Updated: 2022/11/16 14:08:04 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_contour_t(char **map, int i)
{
	int	k;

	k = 0;
	if (map[i][k] == ' ')
	{
		while (map[i][k])
		{
			if (map[i][k] == '1')
				return (1);
			if (!(map[i][k] == ' ' || map[i][k] == '1'
					|| map[i][k] == '\n'))
				return (0);
			k++;
		}
	}
	return (1);
}

int	valid_map(t_game *game)
{
	int	j;

	j = -1;
	while (game->map[++j])
	{
		if (!valid_walls_2(game, game->map, j))
			return (0);
	}
	return (1);
}

int	parse(t_game *game, char *file)
{
	int	test;

	if (init_struct(game, file))
		return (1);
	test = valid_simple_map(game);
	if ((game->simple_map && test == -1) || !test || test == -1)
		return (2);
	if (game->simple_map)
		return (0);
	if (!valid_map(game))
		return (2);
	return (0);
}
