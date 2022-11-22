/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:53:32 by nboratko          #+#    #+#             */
/*   Updated: 2022/11/16 16:38:01 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	real_line_is_it(t_game *game, int j)
{
	game->map[++j] = NULL;
	printf("Error\nWe don't tolerate space after OUR ONE & ONLY MAP....\n");
	return (0);
}

int	check_xpm_format(char *str)
{
	if (str[ft_strlen(str) - 1] != 'm'
		|| str[ft_strlen(str) - 2] != 'p'
		|| str[ft_strlen(str) - 3] != 'x'
		|| str[ft_strlen(str) - 4] != '.')
		return (1);
	return (0);
}

void	init_texture_path_bis(t_game *game, char **tmp, int fd)
{
	int	i;

	while (*tmp)
	{
		i = 0;
		game->intro++;
		while ((*tmp)[i] && (*tmp)[i] == ' ')
			i++;
		if ((*tmp)[i] && ((*tmp)[i] < 9 || (*tmp)[i] > 13))
			get_texture_path(tmp, &game->img, game);
		free(*tmp);
		*tmp = get_next_line(fd);
		if (!*tmp || (game->img.north->path && game->img.south->path
				&& game->img.ceiling_trgb && game->img.floor_trgb))
			break ;
	}
	if (*tmp)
	{
		game->img.floor_clr = create_rgb(ft_atoi(game->img.floor_trgb[0]),
				ft_atoi(game->img.floor_trgb[1]),
				ft_atoi(game->img.floor_trgb[2]));
		game->img.ceiling_clr = create_rgb(ft_atoi(game->img.ceiling_trgb[0]),
				ft_atoi(game->img.ceiling_trgb[1]),
				ft_atoi(game->img.ceiling_trgb[2]));
	}
}

int	init_texture_path(t_game *game, int fd, char **tmp)
{
	game->intro = 0;
	init_texture_path_bis(game, tmp, fd);
	if (*tmp)
	{
		if (check_xpm_format(game->img.north->path)
			|| check_xpm_format(game->img.south->path)
			|| check_xpm_format(game->img.east->path)
			|| check_xpm_format(game->img.west->path))
		{
			printf("Error\nMust be .xpm format");
			free_init_error(game);
		}
	}
	return (0);
}

void	replace_spaces_by_n(char *map)
{
	int	k;

	k = ft_strlen(map) - 2;
	while (k > 0 && map[k] == ' ')
	{
		if (map[k] == ' ')
			map[k] = 10;
		k--;
	}
}
