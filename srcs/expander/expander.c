/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:42:28 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/08 16:14:13 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	count_non_empty_args(char **args)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] != '\0')
		{
			count++;
		}
		i++;
	}
	return (count);
}

char	**remove_empty_args(char **args)
{
	size_t	num_non_empty;
	char	**new_args;
	size_t	i;
	size_t	j;

	num_non_empty = count_non_empty_args(args);
	new_args = gc_malloc((num_non_empty + 1) * sizeof(char *));
	if (!new_args)
		return (NULL);
	j = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] != '\0')
		{
			new_args[j++] = args[i];
		}
		i++;
	}
	new_args[j] = NULL;
	return (new_args);
}

t_token	*expand_tokens(t_token *tokens)
{
	tokens = expand_wildcards(tokens);
	return (tokens);
}
