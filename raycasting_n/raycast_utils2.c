/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:22:58 by nboratko          #+#    #+#             */
/*   Updated: 2022/11/14 17:12:47 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vector	translation(t_vector pos, t_vector dir)
{
	pos.x += dir.x * 1 / 10;
	pos.y += dir.y * 1 / 10;
	return (pos);
}

t_vector	rotation(t_vector vector, double angle)
{
	t_vector	new;

	new = vector;
	if (cos(angle) == 0 && sin(angle) != 0)
	{
		new.x = vector.x * 0.0001 - vector.y * sin(angle);
		new.y = vector.x * sin(angle) + vector.y * 0.0001;
	}
	else if (sin(angle) == 0 && cos(angle) != 0)
	{
		new.x = vector.x * cos(angle) - vector.y * 0.0001;
		new.y = vector.x * 0.0001 + vector.y * cos(angle);
	}
	else
	{
		new.x = vector.x * cos(angle) - vector.y * sin(angle);
		new.y = vector.x * sin(angle) + vector.y * cos(angle);
	}
	return (new);
}

void	put_color(t_pic *pic, int x, int y, int color)
{
	char	*ptr;

	ptr = pic->addr + y * pic->line_len + x * 4;
	*(unsigned int *)ptr = color;
}

void	draw_background(t_game *game)
{
	int	i;
	int	j;

	(void)game;
	i = 0;
	while (i < DIM2)
	{
		j = 0;
		while (j < DIM1)
		{
			put_color(&game->pic, j, i, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	get_wall_x_and_tex(t_game *game)
{
	if (game->rc.side == 0)
		game->rc.wall_x = game->rc.pos.y
			+ game->rc.perp_wall_dist * game->rc.ray.y;
	else
		game->rc.wall_x = game->rc.pos.x
			+ game->rc.perp_wall_dist * game->rc.ray.x;
	game->rc.wall_x -= floor(game->rc.wall_x);
	game->rc.tex_x = (int)(game->rc.wall_x * (double)game->img.north->width);
	if (game->rc.side == 0 && game->rc.ray.x > 0)
		game->rc.tex_x = game->img.north->width - game->rc.tex_x - 1;
	if (game->rc.side == 1 && game->rc.ray.y < 0)
		game->rc.tex_x = game->img.north->width - game->rc.tex_x - 1;
}
