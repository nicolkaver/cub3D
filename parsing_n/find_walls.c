/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:28:40 by nboratko          #+#    #+#             */
/*   Updated: 2022/11/16 14:15:29 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	north_wall(char **map, int i, int k)
{
	while (i >= 0 && map[i][k] != '1')
	{
		if (map[i][k] && map[i][k] != ' ')
		{
			if (map[i][k] == 10)
				return (1);
			return (0);
		}
		if (!map[i - 1][k])
			break ;
		i--;
	}
	if (map[i][k] != '1')
		return (0);
	return (1);
}

int	south_wall(char **map, int i, int k, int height)
{
	while (i < height && map[i][k] != '1')
	{
		if (map[i][k] != ' ')
			return (0);
		if (!map[i + 1][k] || map[i + 1][k] == 10)
			break ;
		i++;
	}
	if (!(map[i][k] == '1' || map[i][k] == ' '))
		return (0);
	return (1);
}

int	west_wall(char **map, int i, int k)
{
	while (map[i][k] && k >= 0 && map[i][k] != '1')
	{
		if (map[i][k] != ' ')
			return (0);
		if (k != 0 && !map[i][k - 1])
			break ;
		k--;
	}
	if (map[i][k] != '1')
		return (0);
	return (1);
}

int	east_wall(char **map, int i, int k)
{
	while (map[i] && map[i][k] != '1')
	{
		if (map[i][k] != ' ')
			return (0);
		if (!map[i][k + 1] || map[i][k + 1] == '\n' || map[i][k + 1] != '1')
			break ;
		k++;
	}
	if (map[i][k] != '1')
		return (0);
	return (1);
}

int	find_a_wall(char **map, int i, int k, int height)
{
	int	north;
	int	south;
	int	west;
	int	east;

	if (i == height - 1)
		return (1);
	north = north_wall(map, i, k);
	south = south_wall(map, i, k, height);
	west = west_wall(map, i, k);
	east = east_wall(map, i, k);
	if (!north || !south || !west || !east)
		return (0);
	return (1);
}
