/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:30:45 by nboratko          #+#    #+#             */
/*   Updated: 2022/11/16 18:46:38 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_stuff(char **path, char **tmp, t_game *game)
{
	free(*path);
	free(*tmp);
	printf("Error\nIncorrect path\n");
	free_init_error(game);
}

void	get_tex_path(char **tmp, t_tex *tex, t_game *game)
{
	int		i;
	int		fd;
	char	*path;

	i = 0;
	if (tex->path != NULL)
	{
		printf("Error\nMultiple definition of a path\n");
		free(*tmp);
		free_init_error(game);
	}
	while ((*tmp)[i] && (*tmp)[i] == ' ')
		i++;
	i += 3;
	while ((*tmp)[i] == ' ')
		i++;
	path = ft_substr(*tmp, i, ft_strlen(*tmp) - i - 1);
	if (!path)
		free_stuff(&path, tmp, game);
	fd = open(path, O_RDWR);
	if (fd < 0)
		free_stuff(&path, tmp, game);
	tex->path = ft_strdup(path);
	free(path);
	close(fd);
}

void	get_texture_path(char **tmp, t_img *img, t_game *game)
{
	int	i;

	i = 0;
	while ((*tmp)[i] && (*tmp)[i] == ' ')
		i++;
	if (ft_strncmp(*tmp, "SO ", 3) == 0)
		get_tex_path(tmp, img->south, game);
	else if (ft_strncmp(*tmp, "NO ", 3) == 0)
		get_tex_path(tmp, img->north, game);
	else if (ft_strncmp(*tmp, "WE ", 3) == 0)
		get_tex_path(tmp, img->west, game);
	else if (ft_strncmp(*tmp, "EA ", 3) == 0)
		get_tex_path(tmp, img->east, game);
	else if ((*tmp)[i] == 'F' || (*tmp)[i] == 'C')
		get_trgb(tmp, game);
	else
	{
		printf("Error\nIncorrect line\n");
		free(*tmp);
		free_init_error(game);
	}
}
