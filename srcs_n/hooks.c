/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:27:49 by nboratko          #+#    #+#             */
/*   Updated: 2022/11/04 15:04:35 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
int	hook_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESCAPE)
		hook_escape(game);
	else if (check_player_movement(keycode, game, game->player))
		player_movements(keycode, game->player);
	return (0);
}
*/
int	render(t_game *game)
{
	apply_moves(game);
	ray_casting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->pic.image, 0, 0);
	return (0);
}

int	close_window(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

int	keypress(int key, t_game *game)
{
	if (key == 119)
		game->up = 1;
	if (key == 97)
		game->left = 1;
	if (key == 115)
		game->down = 1;
	if (key == 100)
		game->right = 1;
	if (key == 65361)
		game->rot_left = 1;
	if (key == 65363)
		game->rot_right = 1;
	return (0);
}

int	keyrelease(int key, t_game *game)
{
	if (key == 65307)
		close_window(game);
	if (key == 119)
		game->up = 0;
	if (key == 97)
		game->left = 0;
	if (key == 115)
		game->down = 0;
	if (key == 100)
		game->right = 0;
	if (key == 65361)
		game->rot_left = 0;
	if (key == 65363)
		game->rot_right = 0;
	return (0);
}
/*
int	hook_escape(t_game *game)
{
	ft_putendl_fd(
		"You have escaped our beautiful game. We hope to see you soon :)", 1);
	free_and_exit(game, 0);
	return (0);
}*/
