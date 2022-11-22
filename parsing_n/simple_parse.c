/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:38:01 by nboratko          #+#    #+#             */
/*   Updated: 2022/11/15 16:35:41 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*if (index == game->height - 1)
 * {
 *		if (map[k] == '0')
			return (0);
	}*/
int	check_walls_bis(t_game *game, char *map, int index, int k)
{
	if (index == game->height && map[k] == '0')
		return (0);
	if ((index != 0 && ((game->map[index - 1][k] >= 9
				&& game->map[index - 1][k] <= 13)
		|| game->map[index - 1][k] == ' ')))
		return (0);
	if (index != game->height - 1 && ((game->map[index + 1][k] >= 9
			&& game->map[index + 1][k] <= 13)
			|| game->map[index + 1][k] == ' '))
		return (0);
	if (index < game->height)
	{
		if ((index != 0 && !game->map[index - 1][k])
			|| (!game->map[index + 1][k])
			|| (k != 0 && !game->map[index][k - 1])
			|| (k != game->width &&!game->map[index][k + 1])
			|| (index != 0 && game->map[index - 1][k] == '\n')
			|| (index != game->height && game->map[index + 1][k]
			== '\n') || (k != 0 && game->map[index][k - 1] == '\n')
			|| (k != game->width && game->map[index][k + 1] == '\n'))
			return (0);
	}
	return (1);
}

static int	opposite_wall(t_game *game, int index, char *map, int k)
{
	if (index == 0)
	{
		while (map[k] && (size_t)k <= ft_strlen(game->map[index + 1])
			&& map[k] == ' ')
		{
			if (game->map[index + 1][k] == '0')
				return (0);
			k++;
		}
	}
	if (index == game->height - 1)
	{
		if (map[k] == ' ')
		{
			while (game->map[index][k] == ' '
				|| game->map[index][k] == '0')
			{
				if (game->map[index][k] == '0')
					return (0);
				index--;
			}
		}
	}
	return (1);
}

int	check_walls(t_game *game, char *map, int index)
{
	int	k;

	k = -1;
	if (!(map[0] == '1' || map[0] == ' ' || map[0] == 10))
		return (0);
	while (map[++k])
	{
		if (!opposite_wall(game, index, map, k))
			return (0);
		if (game->map[index][k] == '0')
		{
			if (!check_walls_bis(game, map, index, k))
				return (0);
		}
		if (!map[k] || map[k] == '\n')
			break ;
		if (map[k + 1] == '\n' && !(map[k] == '1' || map[k] == ' '))
			return (0);
		if ((index == 0 || index == game->width - 1
				|| index == game->height)
			&& !(map[k] == '1' || map[k] == ' '))
			return (0);
	}
	return (1);
}

int	player_on(char *map)
{
	int	k;
	int	player;

	k = -1;
	player = 0;
	while (map[++k])
	{
		if (map[k] == 'N' || map[k] == 'S' || map[k] == 'W' || map[k] == 'E')
			player++;
	}
	return (player);
}

int	valid_simple_map(t_game *game)
{
	int	j;
	int	player;

	j = -1;
	player = 0;
	while (game->map[++j])
	{
		if (!valid_caracters(game->map[j], 0))
			return (printf("Error\nInvalid character found\n"), 0);
		player += player_on(game->map[j]);
		if (!check_walls(game, game->map[j], j))
			return (printf("Error\nWalls not closed\n"), 0);
	}
	if (!player)
		return (printf("Error\nNo player detected\n"), -1);
	else if (player > 1)
		return (printf("Error\nToo many players detected\n"), -1);
	return (1);
}
