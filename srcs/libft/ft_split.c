/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:57:15 by melachyr          #+#    #+#             */
/*   Updated: 2024/04/25 16:26:14 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	sub_strs_count(char const *s, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == sep)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != '\0' && s[i] != sep)
			i++;
	}
	return (count);
}

static char	**free_split_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings[i] != NULL)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
	return (NULL);
}

static char	**get_sub_strs(char **result, const char *s, char sep)
{
	char		**ptr_result;
	const char	*ptr_s;

	ptr_result = result;
	ptr_s = s;
	while (*ptr_s != '\0')
	{
		while (*s == sep)
			s++;
		ptr_s = s;
		while (*ptr_s != '\0' && *ptr_s != sep)
			ptr_s++;
		if (ptr_s > s)
		{
			*ptr_result = ft_substr(s, 0, ptr_s - s);
			if (*ptr_result == NULL)
				return (free_split_strings(result));
			s = ptr_s;
			ptr_result++;
		}
	}
	*ptr_result = NULL;
	return (result);
}

char	**ft_split(char const *s, char sep)
{
	char	**result;
	int		count;

	if (s == NULL)
		return (NULL);
	count = sub_strs_count(s, sep);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (result == NULL)
		return (NULL);
	result = get_sub_strs(result, s, sep);
	return (result);
}
