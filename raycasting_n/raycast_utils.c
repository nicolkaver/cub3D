/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:33:03 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/11/10 16:36:07 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_color(t_tex *tex, int x, int y)
{
	int	*ptr;

	ptr = tex->ptr + tex->size_line * y / 4 + x;
	return (*ptr);
}

void	draw_column(t_game *game, int j, t_tex *tex)
{
	size_t	i;
	double	step;
	int		color;

	i = 0;
	step = (double)tex->height / (double)game->rc.wall_h;
	game->rc.tex_pos = (game->rc.wall_top - DIM2 / 2 + game->rc.wall_h / 2)
		* step;
	while (i < DIM2)
	{
		if (i < (size_t)game->rc.wall_top)
			put_color(&game->pic, j, i, game->img.ceiling_clr);
		else if (i >= (size_t)game->rc.wall_bot)
			put_color(&game->pic, j, i, game->img.floor_clr);
		else
		{
			game->rc.tex_pos += step;
			game->rc.tex_y = (int)game->rc.tex_pos;
			if (game->rc.tex_y > game->img.north->height - 1)
				game->rc.tex_y = game->img.north->height - 1;
			color = get_color(tex, game->rc.tex_y, game->rc.tex_x);
			put_color(&game->pic, j, i, color);
		}
		i++;
	}
}

void	wall_calcs(t_rc *rc)
{
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
	else
		rc->perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);
	rc->wall_h = (int)(DIM2 / rc->perp_wall_dist);
	rc->wall_top = (DIM2 - rc->wall_h) / 2;
	rc->wall_bot = (DIM2 + rc->wall_h) / 2;
	if (rc->wall_top < 0)
		rc->wall_top = 0;
	if (rc->wall_bot >= DIM2)
		rc->wall_bot = DIM2 - 1;
}

void	apply_moves(t_game *game)
{
	if (game->up && mov_up_ok(game) == 1)
		game->rc.pos = translation(game->rc.pos, rotation(game->rc.dir,
					M_PI * (double)UP / 2.0));
	if (game->left && mov_left_ok(game) == 1)
		game->rc.pos = translation(game->rc.pos, rotation(game->rc.dir,
					M_PI * (double)LEFT / 2.0));
	if (game->down && mov_down_ok(game) == 1)
		game->rc.pos = translation(game->rc.pos, rotation(game->rc.dir,
					M_PI * (double)DOWN / 2.0));
	if (game->right && mov_right_ok(game) == 1)
		game->rc.pos = translation(game->rc.pos, rotation(game->rc.dir,
					M_PI * (double)RIGHT / 2.0));
	if (game->rot_left)
			game->rc.dir = rotation(game->rc.dir, M_PI * SPEED);
	if (game->rot_right)
			game->rc.dir = rotation(game->rc.dir, M_PI * -SPEED);
}

void	rc_calcs(t_rc *rc, int x)
{
	rc->camx = (double)x / (double)DIM1 * 2.0 - 1;
	rc->ray.x = rc->dir.x + rc->plane.x * rc->camx;
	rc->ray.y = rc->dir.y + rc->plane.y * rc->camx;
	rc->map.x = (int)rc->pos.x;
	rc->map.y = (int)rc->pos.y;
}
