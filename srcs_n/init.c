/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:05:28 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/11/10 14:30:19 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_malloced_img2(t_tex *tex)
{
	int	x;
	int	y;

	tex->tab = malloc(sizeof(int) * tex->width * tex->height);
	y = 0;
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			tex->tab[y * tex->height + x] = tex->ptr[y * tex->height + x];
			x++;
		}
		y++;
	}
}

static void	init_data_addr(t_game *game)
{
	game->img.south->ptr = (int *)mlx_get_data_addr(game->img.south->img,
			&game->img.south->bpp, &game->img.south->size_line,
			&game->img.south->endian);
	game->img.north->ptr = (int *)mlx_get_data_addr(game->img.north->img,
			&game->img.north->bpp, &game->img.north->size_line,
			&game->img.north->endian);
	game->img.west->ptr = (int *)mlx_get_data_addr(game->img.west->img,
			&game->img.west->bpp, &game->img.west->size_line,
			&game->img.west->endian);
	game->img.east->ptr = (int *)mlx_get_data_addr(game->img.east->img,
			&game->img.east->bpp, &game->img.east->size_line,
			&game->img.east->endian);
	if (!game->img.north->ptr || !game->img.north->ptr || !game->img.east->ptr
		|| !game->img.west->ptr)
		free_init_error(game);
}

void	init_malloced_img(t_game *game)
{
	game->img.south->img = mlx_xpm_file_to_image(game->mlx,
			game->img.south->path, &game->img.south->width,
			&game->img.south->height);
	game->img.north->img = mlx_xpm_file_to_image(game->mlx,
			game->img.north->path, &game->img.north->width,
			&game->img.north->height);
	game->img.west->img = mlx_xpm_file_to_image(game->mlx, game->img.west->path,
			&game->img.west->width, &game->img.west->height);
	game->img.east->img = mlx_xpm_file_to_image(game->mlx, game->img.east->path,
			&game->img.east->width, &game->img.east->height);
	if (!game->img.south->img || !game->img.north->img || !game->img.east->img
		|| !game->img.west->img)
		free_init_error(game);
	init_data_addr(game);
}

int	init_img(t_game *game)
{
	game->img.south = malloc(sizeof(t_tex));
	if (!game->img.south)
		return (printf("Error: failed to malloc img\n"), 2);
	game->img.south->path = NULL;
	game->img.north = malloc(sizeof(t_tex));
	if (!game->img.north)
		return (printf("Error: failed to malloc img\n"), 3);
	game->img.north->path = NULL;
	game->img.west = malloc(sizeof(t_tex));
	if (!game->img.west)
		return (printf("Error: failed to malloc img\n"), 4);
	game->img.west->path = NULL;
	game->img.east = malloc(sizeof(t_tex));
	if (!game->img.east)
		return (printf("Error: failed to malloc img\n"), 5);
	game->img.east->path = NULL;
	return (0);
}
