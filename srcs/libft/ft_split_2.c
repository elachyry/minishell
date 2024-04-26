/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:57:15 by melachyr          #+#    #+#             */
/*   Updated: 2024/04/25 16:26:14 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_white_spaces(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	sub_strs_count(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (is_white_spaces(s[i]))
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != '\0' && !is_white_spaces(s[i]))
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

static char	**get_sub_strs(char **result, const char *s)
{
	char		**ptr_result;
	const char	*ptr_s;

	ptr_result = result;
	ptr_s = s;
	while (*ptr_s != '\0')
	{
		while (is_white_spaces(*s))
			s++;
		ptr_s = s;
		while (*ptr_s != '\0' && !is_white_spaces(*ptr_s))
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

char	**ft_split_2(char const *s)
{
	char	**result;
	int		count;

	if (s == NULL)
		return (NULL);
	count = sub_strs_count(s);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (result == NULL)
		return (NULL);
	result = get_sub_strs(result, s);
	return (result);
}
