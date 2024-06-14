/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:07:19 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/13 15:26:53 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_pattern(const char **string, const char **pattern, \
const char **str_backup, const char **pattern_backup)
{
	if (**pattern == '*')
	{
		*pattern_backup = ++(*pattern);
		*str_backup = *string;
	}
	else if (**pattern == **string)
	{
		(*pattern)++;
		(*string)++;
	}
	else if (*pattern_backup)
	{
		*pattern = *pattern_backup;
		*string = ++(*str_backup);
	}
	else
		return (0);
	return (1);
}

int	match(const char *string, const char *pattern)
{
	const char	*str_backup;
	const char	*pattern_backup;

	str_backup = NULL;
	pattern_backup = NULL;
	while (*string)
	{
		if (!process_pattern(&string, &pattern, &str_backup, &pattern_backup))
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (!*pattern);
}

int	check_wildcard(t_token *tok)
{
	int		has_wildcard;
	char	*tmp;

	has_wildcard = 0;
	tmp = tok->value;
	while (*tmp)
	{
		if (*tmp == '*')
		{
			has_wildcard = 1;
			break ;
		}
		tmp++;
	}
	return (has_wildcard);
}
