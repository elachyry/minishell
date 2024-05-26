/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:42:28 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/26 18:31:24 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*remove_empty_tokens(t_token *tokens)
{
	t_token	*tok;
	t_token	*next_tok;
	t_token	*prev_tok;

	tok = tokens;
	while (tok)
	{
		if (*(tok->value) == '\0')
		{
			next_tok = tok->next;
			prev_tok = tok->prev;
			if (prev_tok)
				prev_tok->next = next_tok;
			else
				tokens = next_tok;
			if (next_tok)
				next_tok->prev = prev_tok;
			free(tok);
			tok = next_tok;
		}
		else
			tok = tok->next;
	}
	return (tokens);
}

t_token	*expand_tokens(t_token *tokens)
{
	// tokens = expand_env_variable(tokens);
	// tokens = remove_empty_tokens(tokens);
	// tokens = expand_quotes(tokens);
	// tokens = expand_wildcards(tokens);
	return (tokens);
}
