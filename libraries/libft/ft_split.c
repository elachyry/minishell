/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:22:12 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/06 16:02:57 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_freeup(char **res)
{
	int	i;

	i = 0;
	while (res[i] != NULL)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

static char	**ft_allocate(char **res, char const *s, char sep)
{
	char		**tab;
	char const	*tmp;

	tab = res;
	tmp = s;
	while (*tmp)
	{
		while (*s == sep)
			++s;
		tmp = s;
		while (*tmp && *tmp != sep)
			++tmp;
		if (tmp > s)
		{
			*tab = ft_substr(s, 0, tmp - s);
			if (!*tab)
				return (ft_freeup(res));
			s = tmp;
			++tab;
		}
	}
	*tab = NULL;
	return (res);
}

static int	word_count(char const *s, char sep)
{
	int	size;

	size = 0;
	while (*s)
	{
		while (*s == sep)
			++s;
		if (*s)
			++size;
		while (*s && *s != sep)
			++s;
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		size;

	if (s == NULL)
		return (NULL);
	size = word_count(s, c);
	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		return (NULL);
	res = ft_allocate(res, s, c);
	return (res);
}
