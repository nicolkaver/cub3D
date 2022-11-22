/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:50:27 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/11/16 18:52:32 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	deltadist(t_rc *rc)
{
	if (rc->ray.x == 0)
		rc->delta_dist_x = INT_MAX;
	else
		rc->delta_dist_x = fabs(1.0 / rc->ray.x);
	if (rc->ray.y == 0)
		rc->delta_dist_y = INT_MAX;
	else
		rc->delta_dist_y = fabs(1.0 / rc->ray.y);
}

void	pre_dda(t_rc *rc)
{
	deltadist(rc);
	if (rc->ray.x < 0)
	{
		rc->step_x = -1;
	rc->side_dist_x = (rc->pos.x - (double)rc->map.x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = ((double)rc->map.x + 1.0 - rc->pos.x)
			* rc->delta_dist_x;
	}
	if (rc->ray.y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->pos.y - (double)rc->map.y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = ((double)rc->map.y + 1.0 - rc->pos.y)
			* rc->delta_dist_y;
	}
}

// trouver un nom + explicite pour se souvenir ce qu'elle fait
static void	dda_bis(t_game *game, t_rc *rc)
{
	if (rc->side_dist_x < rc->side_dist_y)
	{
		rc->side_dist_x += rc->delta_dist_x;
		rc->map.x += rc->step_x;
		rc->side = 0;
		if (rc->step_x == 1)
			game->img.id = 0;
		else
			game->img.id = 1;
	}
	else
	{
		rc->side_dist_y += rc->delta_dist_y;
		rc->map.y += rc->step_y;
		rc->side = 1;
		if (rc->step_y == 1)
			game->img.id = 2;
		else
			game->img.id = 3;
	}
}

void	dda(t_game *game, t_rc *rc)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		dda_bis(game, rc);
		if (game->map[rc->map.y][rc->map.x] == '1')
			hit = 1;
	}
}

void	ray_casting(t_game *game)
{
	size_t	j;

	game->rc.plane = rotation(game->rc.dir, -M_PI / 2);
	j = 0;
	while (j < DIM1)
	{
		rc_calcs(&game->rc, j);
		pre_dda(&game->rc);
		dda(game, &game->rc);
		wall_calcs(&game->rc);
		get_wall_x_and_tex(game);
		if (game->img.id == 0)
			draw_column(game, j, game->img.east);
		else if (game->img.id == 2)
			draw_column(game, j, game->img.north);
		else if (game->img.id == 1)
			draw_column(game, j, game->img.west);
		else
			draw_column(game, j, game->img.south);
		j++;
	}
}

/*
static void	deltadist(t_rc *rc)
{
	if (rc->ray.x == 0)
		rc->delta_dist_x = INT_MAX;
	else
		rc->delta_dist_x = fabs(1.0 / rc->ray.x);
	if (rc->ray.y == 0)
		rc->delta_dist_y = INT_MAX;
	else
		rc->delta_dist_y = fabs(1.0 / rc->ray.y);
}

void	pre_dda(t_rc *rc)
{
	deltadist(rc);
	if (rc->ray.x < 0)
	{
		rc->step_x = -1;
	rc->side_dist_x = (rc->pos.x - (double)rc->map.x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = ((double)rc->map.x + 1.0 - rc->pos.x)
			* rc->delta_dist_x;
	}
	if (rc->ray.y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->pos.y - (double)rc->map.y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = ((double)rc->map.y + 1.0 - rc->pos.y)
			* rc->delta_dist_y;
	}
}

// trouver un nom + explicite pour se souvenir ce qu'elle fait
static void	dda_bis(t_game *game, t_rc *rc)
{
	if (rc->side_dist_x < rc->side_dist_y)
	{
		rc->side_dist_x += rc->delta_dist_x;
		rc->map.x += rc->step_x;
		rc->side = 0;
		if (rc->step_x == 1)
			game->img.id = 0;
		else
			game->img.id = 1;
	}
	else
	{
		rc->side_dist_y += rc->delta_dist_y;
		rc->map.y += rc->step_y;
		rc->side = 1;
		if (rc->step_y == 1)
			game->img.id = 2;
		else
			game->img.id = 3;
	}
}

void	dda(t_game *game, t_rc *rc)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		dda_bis(game, rc);
		if (game->map[rc->map.y][rc->map.x] == '1')
			hit = 1;
	}
}

void	ray_casting(t_game *game)
{
	size_t	j;

	game->rc.plane = rotation(game->rc.dir, -M_PI / 2);
	j = 0;
	while (j < DIM1)
	{
		rc_calcs(&game->rc, j);
		pre_dda(&game->rc);
		dda(game, &game->rc);
		wall_calcs(&game->rc);
		get_wall_x_and_tex(game);
		if (game->img.id == 0)
			draw_column(game, j, game->img.east);
		else if (game->img.id == 1)
			draw_column(game, j, game->img.north);
		else if (game->img.id == 2)
			draw_column(game, j, game->img.west);
		else
			draw_column(game, j, game->img.south);
		j++;
	}
}

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
}*/
