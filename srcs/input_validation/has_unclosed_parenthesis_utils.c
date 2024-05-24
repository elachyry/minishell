/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_unclosed_parenthesis_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:32:39 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/24 16:14:01 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	h_o_p(int *open, char *prev_ns, t_bool *non_ws_enc)
{
	if (*prev_ns && !ft_isspace(*prev_ns)
		&& *prev_ns != '|' && *prev_ns != '&'
		&& *prev_ns != '"' && *prev_ns != '\'')
	{
		return (false);
	}
	(*open)++;
	*non_ws_enc = false;
	return (true);
}

t_bool	h_c_p(char **input, int *open, t_bool *non_ws_enc, t_bool *after_cp)
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
