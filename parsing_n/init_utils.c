/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:39:29 by nboratko          #+#    #+#             */
/*   Updated: 2022/11/16 19:09:57 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_mapsize2(t_game *game, char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\n'))
			i++;
	if (tmp[i])
		game->height++;
	if ((unsigned int)game->width < ft_strlen(tmp) - 1)
		game->width = (int)ft_strlen(tmp) - 1;
}

int	get_mapsize(t_game *game)
{
	char	*tmp;
	int		fd;

	fd = open(game->av, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCannot open the map\n"), 0);
	tmp = get_next_line(fd);
	if (!tmp)
		return (get_next_line(-1), printf("Error\nNothing to read\n"), 0);
	if (init_texture_path(game, fd, &tmp) == 1 || fd < 0)
		return (printf("Error\n%s: %s\n", game->av, strerror(errno)), 0);
	while (tmp)
	{
		get_mapsize2(game, tmp);
		free(tmp);
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		if (game->width && game->width != (int)ft_strlen(tmp) - 1)
			game->simple_map = 0;
	}
	free(tmp);
	if (!game->height || !game->width)
		return (printf("Error\nDimension not valid or empty map\n"), 0);
	return (get_next_line(-1), close(fd), 1);
}

int	is_real_line(t_game *game, char *map, int test, int j)
{
	int	i;

	i = 0;
	while (map[i] && ((map[i] >= 9 && map[i] <= 13) || map[i] == ' '))
		i++;
	if (!map[i] && test == -1)
		return (free(game->map[j]), 0);
	return (1);
}

static int	get_actual_map(t_game *game, int fd)
{
	int	j;
	int	test;
	int	var;

	j = 0;
	test = -1;
	game->map[j] = get_next_line(fd);
	if (!game->map[j])
		return (get_next_line(-1), printf("Error\nNothing to read\n"), 0);
	while (game->map[j])
	{
		var = is_real_line(game, game->map[j], test, j);
		if (var == 1)
		{
			test = 1;
			j++;
		}
		game->map[j] = get_next_line(fd);
		if (!game->map[j])
			break ;
		replace_spaces_by_n(game->map[j]);
	}
	return (get_next_line(-1), 1);
}

int	get_map(t_game *game, char *file)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\n%s: %s\n", file, strerror(errno)), 0);
	game->map = malloc(sizeof(char *) * ((game->height + 1)
				* (game->width + 1)));
	if (!game->map)
		return (printf("Error\nMap malloc failed\n"), 0);
	while (i < game->intro)
	{
		game->map[0] = get_next_line(fd);
		i++;
		free(game->map[0]);
	}
	if (!get_actual_map(game, fd))
	{
		get_next_line(-1);
		return (0);
	}
	get_next_line(-1);
	close(fd);
	return (1);
}
