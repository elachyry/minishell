/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_unclosed_parenthesis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 01:07:45 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/13 15:27:38 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_vars(t_parenthesis_data *data)
{
	data->open = 0;
	data->prev_ns = 0;
	data->non_ws_enc = false;
	data->after_cp = false;
	data->s_q = 0;
	data->d_q = 0;
}

static void	initialization(char **input, char *prev_ns, t_bool *non_ws_enc)
{
	*non_ws_enc = true;
	*prev_ns = **input;
}

t_bool	has_unclosed_parenthesis(char *input)
{
	t_parenthesis_data	data;

	init_vars(&data);
	while (*input)
	{
		update_quote_counts(*input, &data.s_q, &data.d_q);
		if (!(data.d_q % 2 || data.s_q % 2) \
			&& *input == '(')
		{
			if (!h_o_p(&data.open, &data.prev_ns, &data.non_ws_enc))
				return (false);
		}
		else if (!(data.d_q % 2 || data.s_q % 2) \
			&& *input == ')')
		{
			if (!h_c_p(&input, &data.open, &data.non_ws_enc, &data.after_cp))
				return (false);
		}
		else if (!handle_after_closing_parenthesis(&input, &data.after_cp))
			return (false);
		else if (!ft_isspace(*input))
			initialization(&input, &data.prev_ns, &data.non_ws_enc);
		input++;
	}
	return (data.open == 0);
}
