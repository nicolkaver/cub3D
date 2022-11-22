/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:24:33 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/11/15 16:34:38 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_space_valid(char **trgb, int i)
{
	int	j;
	int	color;

	color = 0;
	j = 0;
	while ((trgb[i][j] >= 9 && trgb[i][j] <= 13) || trgb[i][j] == ' ')
		j++;
	while (trgb[i][j])
	{
		if (!ft_isdigit(trgb[i][j]))
			color = 1;
		if (color && ((trgb[i][j] >= 9 && trgb[i][j] <= 13)
			|| trgb[i][j] == ' '))
		{
			j++;
			if (!ft_isdigit(trgb[i][j]))
				return (0);
		}
		j++;
	}
	return (1);
}

unsigned int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	my_mlx_pixel_put(t_pic *pic, int x, int y, int color)
{
	char	*dst;

	dst = pic->addr + (y * pic->line_len + x * (pic->bits_pp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_tex *tex, int x, int y)
{
	long int	lol;

	lol = (long int)(tex->ptr + y * tex->size_line
			+ x * (tex->bpp / 8));
	return (lol);
}
