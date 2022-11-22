/* ************************************************************************** */
/*                                                                           */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:21:07 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/11/15 14:35:08 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_trgb(char **trgb, t_game *game, char **buff, char **tmp)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (trgb[++i])
	{
		j = 0;
		while (trgb[i][j])
		{
			if (trgb[i][j] == ',')
				k++;
			if ((!ft_isdigit(trgb[i][j]) && trgb[i][j] != ' ')
				|| ft_atoi(trgb[i]) > 255 || k > 2 || !is_space_valid(trgb, i))
			{
				free_split(trgb);
				free_split(buff);
				free(*tmp);
				printf("Error\nWrong color format\n");
				free_init_error(game);
			}
			j++;
		}
	}
}

void	check_buff_and_trgb(char **buff, char **trgb, t_game *game, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buff[i])
		i++;
	while (trgb[j])
		j++;
	if (j != 3)
	{
		free_split(trgb);
		free_split(buff);
		free(*tmp);
		printf("Error\nSomething went wrong with your F or C\n");
		free_init_error(game);
	}
	check_trgb(trgb, game, buff, tmp);
}

void	get_trgb_bis(t_game *game, char **trgb, char **buff, char **tmp)
{
	if (ft_strncmp(buff[0], "C", 1) == 0 && game->img.ceiling_trgb == NULL)
		game->img.ceiling_trgb = trgb;
	else if (ft_strncmp(buff[0], "F", 1) == 0 && game->img.floor_trgb == NULL)
		game->img.floor_trgb = trgb;
	else
	{
		free_split(trgb);
		free_split(buff);
		free(*tmp);
		printf("Error\nwrong definition of F or C\n");
		free_init_error(game);
	}
}

static char	**get_trgb_buf(char *temp)
{
	int		i;
	char	**buf;

	i = 0;
	while (!ft_isdigit(temp[i]))
		i++;
	if (temp)
	{
		buf = malloc(sizeof(char *) * 3);
		buf[0] = ft_substr(temp, 0, i);
		buf[1] = ft_substr(temp, i, ft_strlen(temp));
		buf[2] = NULL;
	}
	else
		buf = NULL;
	return (buf);
}

void	get_trgb(char **tmp, t_game *game)
{
	char	**trgb;
	char	**buff;
	char	*temp;

	temp = ft_substr(*tmp, 0, ft_strlen(*tmp) - 1);
	if (!temp)
		free_init_error(game);
	buff = get_trgb_buf(temp);
	free(temp);
	if (!buff)
	{
		printf("Error: malloc failed\n");
		free(*tmp);
		free_init_error(game);
	}
	trgb = ft_split(buff[1], ',');
	if (!trgb)
	{
		free_split(buff);
		free(*tmp);
		free_init_error(game);
	}
	check_buff_and_trgb(buff, trgb, game, tmp);
	get_trgb_bis(game, trgb, buff, tmp);
	free_split(buff);
}
