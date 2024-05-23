/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:07:14 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/23 01:10:03 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	toggle_quotes(char current_char, t_quote_state *quote_state)
{
	if (current_char == '\'')
	{
		if (!quote_state->in_double_quotes)
			quote_state->in_single_quotes = !quote_state->in_single_quotes;
		else
			quote_state->nested_quotes = !quote_state->nested_quotes;
	}
	else if (current_char == '\"')
	{
		if (!quote_state->in_single_quotes)
			quote_state->in_double_quotes = !quote_state->in_double_quotes;
		else
			quote_state->nested_quotes = !quote_state->nested_quotes;
	}
}

char	*handle_variable_expansion(char *line, char **ret, \
t_quote_state *quote_state)
{
	char	*value;

	if (*line == '$' && (!quote_state->in_single_quotes
			|| (quote_state->in_double_quotes && !quote_state->nested_quotes)))
	{
		line = fetch_variable_value(&value, line + 1, \
		g_shell_data.environment_list);
		*ret = ft_strjoin(*ret, value);
		return (line);
	}
	*ret = concatenate_char(*ret, *line);
	return (line);
}

char	*shearch_and_replace(char *line)
{
	char			*ret;
	t_quote_state	quote_state;

	ret = "";
	quote_state.in_single_quotes = 0;
	quote_state.in_double_quotes = 0;
	quote_state.nested_quotes = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			toggle_quotes(*line, &quote_state);
			ret = concatenate_char(ret, *line);
		}
		else
			line = handle_variable_expansion(line, &ret, &quote_state);
		line++;
	}
	return (ret);
}

void	handle_token_value(t_token *tok)
{
	int		in_single_quotes;
	int		in_double_quotes;
	char	*tmp;

	in_single_quotes = 0;
	in_double_quotes = 0;
	tmp = tok->value;
	while (*tmp)
	{
		if (*tmp == '\'')
			in_single_quotes = !in_single_quotes;
		else if (*tmp == '\"')
			in_double_quotes = !in_double_quotes;
		else if (*tmp == '$' && (!in_single_quotes || in_double_quotes))
		{
			tok->value = shearch_and_replace(tok->value);
			break ;
		}
		tmp++;
	}
}

t_token	*expand_env_variable(t_token *tokens)
{
	t_token	*tok;

	tok = tokens;
	while (tok)
	{
		if (tok->prev && tok->prev->type == DoubleLessThanOperator)
		{
			tok = tok->next;
			continue ;
		}
		handle_token_value(tok);
		tok = tok->next;
	}
	return (tokens);
}

/*
char	*shearch_and_replace(char *line)
{
	char	*ret;
	char	*value;
	int		in_single_quotes;
	int		in_double_quotes;
	int		nested_quotes;

	ret = "";
	in_single_quotes = 0;
	in_double_quotes = 0;
	nested_quotes = 0;
	while (*line)
	{
		if (*line == '\'')
		{
			if (!in_double_quotes)
				in_single_quotes = !in_single_quotes;
			else
				nested_quotes = !nested_quotes;
			ret = append_char(ret, *line);
		}
		else if (*line == '\"')
		{
			if (!in_single_quotes)
				in_double_quotes = !in_double_quotes;
			else
				nested_quotes = !nested_quotes;
			ret = append_char(ret, *line);
		}
		else if (*line == '$' && (!in_single_quotes
			|| (in_double_quotes && !nested_quotes)))
		{
			line = get_var_value(&value, line + 1, \
			g_shell_data.environment_list);
			ret = ft_strjoin(ret, value);
		}
		else
			ret = append_char(ret, *line);
		line++;
	}
	return (ret);
}
*/