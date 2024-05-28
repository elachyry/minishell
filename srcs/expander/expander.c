/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:42:28 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/28 19:12:18 by akaddour         ###   ########.fr       */
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
	new_args = malloc((num_non_empty + 1) * sizeof(char *));
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
		else
		{
			free(args[i]);
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

// t_token	*remove_empty_tokens(t_token *tokens)
// {
// 	t_token	*tok;
// 	t_token	*next_tok;
// 	t_token	*prev_tok;

// 	tok = tokens;
// 	while (tok)
// 	{
// 		if (*(tok->value) == '\0')
// 		{
// 			next_tok = tok->next;
// 			prev_tok = tok->prev;
// 			if (prev_tok)
// 				prev_tok->next = next_tok;
// 			else
// 				tokens = next_tok;
// 			if (next_tok)
// 				next_tok->prev = prev_tok;
// 			free(tok);
// 			tok = next_tok;
// 		}
// 		else
// 			tok = tok->next;
// 	}
// 	return (tokens);
// }