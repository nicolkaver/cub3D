/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:41:53 by jcourtoi          #+#    #+#             */
/*   Updated: 2021/12/03 18:01:42 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_carcount(const char *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

static unsigned int	ft_wordcount(const char *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			i = i + ft_carcount(&s[i], c);
		}
		else
			i++;
	}
	return (count);
}

static void	ft_protect(const char *s)
{
	if (!s)
		return ;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**split;

	ft_protect(s);
	split = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			split[j] = malloc(sizeof(char) * (ft_carcount(&s[i], c) + 1));
			if (!split[j])
				return (NULL);
			ft_strlcpy(split[j++], &s[i], ft_carcount(&s[i], c) + 1);
			i = i + ft_carcount(&s[i], c);
		}
		else
			i++;
	}
	split[j] = NULL;
	return (split);
}
