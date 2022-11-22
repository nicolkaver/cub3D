/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:43:16 by nboratko          #+#    #+#             */
/*   Updated: 2022/11/16 18:52:53 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_struct(t_game *game, char *file)
{
	int	mapsize;

	game->simple_map = 1;
	game->av = file;
	game->width = 0;
	game->height = 0;
	init_img(game);
	game->img.north->path = NULL;
	game->img.south->path = NULL;
	game->img.east->path = NULL;
	game->img.west->path = NULL;
	mapsize = get_mapsize(game);
	if (!mapsize)
		return (2);
	if (!get_map(game, file))
		return (3);
	return (0);
}

void	get_dir(t_game *game)
{
	if (game->start == 'S')
		game->rc.dir.y = -1;
	else if (game->start == 'N')
		game->rc.dir.y = 1;
	else if (game->start == 'E')
		game->rc.dir.x = 1;
	else if (game->start == 'W')
		game->rc.dir.x = -1;
}

void	init_vars(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->rc.pos.x = j;
				game->rc.pos.y = i;
				game->start = game->map[i][j];
				game->map[i][j] = '0';
			}
			j++;
		}
	}
	get_dir(game);
}
