/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:07:14 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/10 23:35:07 by akaddour         ###   ########.fr       */
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

char	*process_arg(char *arg, t_bool *is_var)
{
	char	*tmp;

	tmp = arg;
	while (*tmp)
	{
		if (*tmp == '$')
		{
			*is_var = true;
			arg = shearch_and_replace(arg);
			break ;
		}
		tmp++;
	}
	return (arg);
}

void	expand_env_variable(char **args)
{
	int		i;
	t_bool	is_var;

	if (!args)
		return ;
	i = 0;
	is_var = false;
	while (args[i])
	{
		args[i] = process_arg(args[i], &is_var);
		i++;
	}
	i = -1;
	while (args[++i] && is_var)
	{
		if (args[i][0] == '\0')
			g_shell_data.simple_cmd->is_var = true;
	}
}
