/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:47:50 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/11/16 15:32:48 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_game *game)
{
	int	j;

	j = 0;
	while (game->map[j])
	{
		free(game->map[j]);
		j++;
	}
	free(game->map);
	game->map = NULL;
}

void	free_malloced_img(t_tex *tex)
{
	free(tex->tab);
	free(tex->path);
	free(tex);
}

void	free_mlx(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img.north->img);
	mlx_destroy_image(game->mlx, game->img.south->img);
	mlx_destroy_image(game->mlx, game->img.east->img);
	mlx_destroy_image(game->mlx, game->img.west->img);
	free_split(game->img.floor_trgb);
	free_split(game->img.ceiling_trgb);
	mlx_destroy_image(game->mlx, game->pic.image);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	free_game(t_game *game, int loop)
{
	(void)loop;
	free_mlx(game);
	free_malloced_img(game->img.north);
	free_malloced_img(game->img.south);
	free_malloced_img(game->img.east);
	free_malloced_img(game->img.west);
	free_map(game);
}

void	free_and_exit(t_game *game, int exit_code)
{
	if (game->mlx)
		free_game(game, 1);
	if (game->map)
		free_map(game);
	exit(exit_code);
}
