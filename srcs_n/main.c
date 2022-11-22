/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:49:55 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/11/09 17:25:57 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (printf("Error\nMLX init failed\n"), 0);
	game->win = mlx_new_window(game->mlx, DIM1, DIM2, "test");
	if (!game->win)
		return (free(game->mlx), printf("Error\nmlx new win failed\n"), 0);
	game->pic.image = mlx_new_image(game->mlx, DIM1, DIM2);
	if (!game->pic.image)
		return (free(game->win), free(game->mlx),
			printf("Error\nMlx new img failed\n"), 0);
	game->pic.addr = mlx_get_data_addr(game->pic.image,
			&game->pic.bits_pp, &game->pic.line_len, &game->pic.endian);
	if (!game->pic.addr)
		return (free(game->pic.image), free(game->win), free(game->mlx),
			printf("Error\nMlx get data addr failed\n"), 0);
	init_malloced_img(game);
	init_malloced_img2(game->img.north);
	init_malloced_img2(game->img.south);
	init_malloced_img2(game->img.east);
	init_malloced_img2(game->img.west);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (check_args(ac, av))
		return (1);
	ft_bzero(&game, sizeof(t_game));
	ft_bzero(&game.img, sizeof(t_img));
	ft_bzero(&game.img.north, sizeof(t_tex));
	ft_bzero(&game.img.south, sizeof(t_tex));
	ft_bzero(&game.img.west, sizeof(t_tex));
	ft_bzero(&game.img.east, sizeof(t_tex));
	if (parse(&game, av[1]))
		free_init_error(&game);
	init_vars(&game);
	init_mlx(&game);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	mlx_hook(game.win, 2, 1L << 0, keypress, &game);
	mlx_hook(game.win, 3, 1L << 1, keyrelease, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	free_game(&game, 0);
	return (0);
}
