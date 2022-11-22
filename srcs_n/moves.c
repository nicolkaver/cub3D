/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:21:26 by nboratko          #+#    #+#             */
/*   Updated: 2022/11/10 16:51:01 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/*
int	diago_move_ok(t_game *game, t_vector pos)
{
	//(void)game, (void)pos;
	if (game->map[(int)pos.y + 1][(int)pos.x] != '0')
		return (0);
//	if (game->map[(int)pos.y + 1][(int)pos.x + 1] != '0')
//		return (0);
	if (game->map[(int)pos.y][(int)pos.x + 1] != '0')
		return (0);
	if (game->map[(int)pos.y - 1][(int)pos.x] != '0')
		return (0);
//	if (game->map[(int)pos.y - 1][(int)pos.x - 1] != '0')
//		return (0);
	if (game->map[(int)pos.y][(int)pos.x] != '0')
		return (0);
	return (1);
}
*/
int	mov_up_ok(t_game *game)
{
	t_vector	pos;

	pos.x = game->rc.pos.x;
	pos.y = game->rc.pos.y;
	pos = translation(pos, rotation(game->rc.dir,
				M_PI * (double)UP / 2.0));
	if (game->map[(int)pos.y][(int)pos.x] != '0')
		return (0);
	return (1);
}

int	mov_down_ok(t_game *game)
{
	t_vector	pos;

	pos.x = game->rc.pos.x;
	pos.y = game->rc.pos.y;
	pos = translation(pos, rotation(game->rc.dir,
				M_PI * (double)DOWN / 2.0));
	if (game->map[(int)pos.y][(int)pos.x] != '0')
		return (0);
	return (1);
}

int	mov_left_ok(t_game *game)
{
	t_vector	pos;

	pos.x = game->rc.pos.x;
	pos.y = game->rc.pos.y;
	pos = translation(pos, rotation(game->rc.dir,
				M_PI * (double)LEFT / 2.0));
	if (game->map[(int)pos.y][(int)pos.x] != '0')
		return (0);
	return (1);
}

int	mov_right_ok(t_game *game)
{
	t_vector	pos;

	pos.x = game->rc.pos.x;
	pos.y = game->rc.pos.y;
	pos = translation(pos, rotation(game->rc.dir,
				M_PI * (double)RIGHT / 2.0));
	if (game->map[(int)pos.y][(int)pos.x] != '0')
		return (0);
	return (1);
}
