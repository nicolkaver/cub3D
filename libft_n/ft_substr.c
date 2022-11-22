/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:50:15 by jcourtoi          #+#    #+#             */
/*   Updated: 2021/12/03 20:07:02 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_len(const char *s, unsigned int start, size_t len)
{
	size_t	size;

	size = 0;
	if ((start + len) <= ft_strlen(s))
		size = len;
	if ((start + len) > ft_strlen(s))
	{
		while (s[start + size])
			size++;
	}
	return (size);
}	

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	size = ft_len(s, start, len);
	i = 0;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (s[start + i] && i < size)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
