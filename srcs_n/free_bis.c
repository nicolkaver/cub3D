/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:00:28 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/11/14 13:42:12 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_failed_img_bis(t_game *game, int which)
{
	if (which == 4)
	{
		free(game->img.north);
		which--;
	}
	if (which == 3)
	{
		free(game->img.south);
		which--;
	}
}

void	free_failed_img(t_game *game, int which)
{
	if (which == 7)
		which--;
	if (which == 6)
	{
		free(game->img.east);
		which--;
	}
	if (which == 5)
	{
		free(game->img.west);
		which--;
	}
	else
		free_failed_img_bis(game, which);
	exit(EXIT_FAILURE);
}

void	free_img(t_game *game)
{
	free(game->img.east);
	free(game->img.west);
	free(game->img.north);
	free(game->img.south);
}

void	free_init_error(t_game *game)
{
	if (game->img.north->path)
		free(game->img.north->path);
	if (game->img.west->path)
		free(game->img.west->path);
	if (game->img.south->path)
		free(game->img.south->path);
	if (game->img.east->path)
		free(game->img.east->path);
	if (game->img.ceiling_trgb)
		free_split(game->img.ceiling_trgb);
	if (game->img.floor_trgb)
		free_split(game->img.floor_trgb);
	free_img(game);
	get_next_line(-1);
	free_and_exit(game, 1);
}

void	free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
