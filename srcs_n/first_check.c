/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:49:32 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/11/14 16:49:40 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_valid_dim(void)
{
	if (DIM1 < 1 || DIM2 < 1)
		return (0);
	if (ft_isalpha(DIM1) || ft_isalpha(DIM2))
		return (0);
	return (1);
}

static int	check_cub_format(char *str)
{
	if (str[ft_strlen(str) - 1] != 'b'
		|| str[ft_strlen(str) - 2] != 'u'
		|| str[ft_strlen(str) - 3] != 'c'
		|| str[ft_strlen(str) - 4] != '.')
		return (1);
	return (0);
}

static int	cub_file(char *av)
{
	char	*ext_found;
	char	*tmp;
	int		fd;

	fd = open(av, O_RDWR);
	if (fd < 0)
		return (printf("Error\nFile not correct\n"), 0);
	close(fd);
	tmp = ft_strchr(av, '/');
	if (tmp)
	{
		if (ft_strlen(tmp) == 5)
			return (printf("Error\nExpected ext: .cub file\n"), 0);
	}
	ext_found = ft_strnstr(av, ".cub", ft_strlen(av));
	if (!ext_found)
		return (printf("Error\nExpected ext : .cub file\n"), 0);
	else if (check_cub_format(av))
		return (printf("Error\nExpected ext : .cub file\n"), 0);
	return (1);
}

	//else if (ft_strlen(ext_found) != 4)

int	valid_caracters(char *s, int av)
{
	int	j;
	int	dot;

	dot = 0;
	j = -1;
	while (s[++j])
	{
		if (av && !(s[j] == '_' || s[j] == '-' || s[j] == '.'
				|| ft_isalnum(s[j]) || s[j] == '/'))
			return (0);
		if (av && s[j] == '.')
			dot++;
		if (!av && !(s[j] == '1' || s[j] == '0' || s[j] == 'N' || s[j] == 'W'
				|| s[j] == 'S' || s[j] == 'E' || s[j] == 10 || s[j] == 9
				|| s[j] == '\n' || s[j] == ' '))
			return (0);
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	if (!is_valid_dim())
		return (printf("Error\nResolution not valid\n"), 1);
	if (ac != 2)
		return (printf("Error\nFormat expected : <./cub3D <map>.cub>\n"), 1);
	else if (!cub_file(av[1]))
		return (2);
	else if (!valid_caracters(av[1], 1))
		return (printf("Error\nWeird characters found\n"), 3);
	return (0);
}
