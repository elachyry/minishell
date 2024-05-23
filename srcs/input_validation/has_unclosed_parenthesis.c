/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_unclosed_parenthesis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 01:07:45 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/23 02:53:10 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_vars(int *open, char *prev_ns, \
t_bool *non_ws_enc, t_bool *after_cp)
{
	*open = 0;
	*prev_ns = 0;
	*non_ws_enc = false;
	*after_cp = false;
}

t_bool	handle_opening_parenthesis(int *open, \
char *prev_ns, t_bool *non_ws_enc)
{
	if (*prev_ns && !ft_isspace(*prev_ns)
		&& *prev_ns != '|' && *prev_ns != '&'
		&& *prev_ns != '"' && *prev_ns != '\'')
		return (false);
	(*open)++;
	*non_ws_enc = false;
	return (true);
}

t_bool	handle_close_par(char **input, int *open, \
t_bool *non_ws_enc, t_bool *after_cp)
{
	const char	*temp;

	if (*open == 0 || !(*non_ws_enc))
		return (false);
	(*open)--;
	temp = (*input) - 1;
	while (ft_isspace(*temp))
		temp--;
	if (*temp == '>' || *temp == '<')
		return (false);
	(*after_cp) = true;
	return (true);
}

t_bool	handle_after_closing_parenthesis(char **input, t_bool *after_cp)
{
	if (*after_cp && !ft_isspace(**input))
	{
		if (**input == '>' || **input == '<'
			|| **input == '|' || **input == '&')
			*after_cp = false;
		else
			return (false);
	}
	return (true);
}

static void	initialization(char **input, char *prev_ns, t_bool *non_ws_enc)
{
	*non_ws_enc = true;
	*prev_ns = **input;
}

t_bool	has_unclosed_parenthesis(char *input)
{
	int			open;
	char		prev_ns;
	t_bool		non_ws_enc;
	t_bool		after_cp;
	int			s_q_count;
	int			d_q_count;

	s_q_count = 0;
	d_q_count = 0;
	init_vars(&open, &prev_ns, &non_ws_enc, &after_cp);
	while (*input)
	{
		update_quote_counts(*input, &s_q_count, &d_q_count);
		if (!(d_q_count || s_q_count) && *input == '(')
		{
			if (!handle_opening_parenthesis(&open, &prev_ns, &non_ws_enc))
				return (false);
		}
		else if (!(d_q_count || s_q_count) && *input == ')')
		{
			if (!handle_close_par(&input, &open, &non_ws_enc, &after_cp))
				return (false);
		}
		else if (!handle_after_closing_parenthesis(&input, &after_cp))
			return (false);
		else if (!ft_isspace(*input))
			initialization(&input, &prev_ns, &non_ws_enc);
		input++;
	}
	return (open == 0);
}
