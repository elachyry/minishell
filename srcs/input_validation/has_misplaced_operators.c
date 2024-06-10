/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_misplaced_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:41:36 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/09 02:37:02 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_var(t_operator_data *data)
{
	data->next_command = 0;
	data->s_q = 0;
	data->d_q = 0;
	data->enc_and_or = false;
	data->temp = NULL;
}

t_bool	is_misplaced_operator(const char *input, t_operator_data *data)
{
	if (*(input + 1) == ')' || *(input - 1) == '(')
		return (true);
	if (!data->enc_and_or)
	{
		data->enc_and_or = true;
		data->temp = input + 1;
		if (*data->temp == *input)
		{
			if (*(++data->temp) == *input)
				return (true);
		}
	}
	if (data->next_command)
		return (true);
	data->next_command = 1;
	return (false);
}

t_bool	has_misplaced_operators(const char *input)
{
	t_operator_data	data;

	init_var(&data);
	if ((*input == '|' || *input == '&'))
		return (false);
	while (*input)
	{
		update_quote_counts(*input, &data.s_q, &data.d_q);
		if (!(data.s_q % 2) && !(data.d_q % 2)
			&& (*input == '|' || *input == '&'))
		{
			if (is_misplaced_operator(input, &data))
				return (false);
			if (*(input + 1) == *input)
				input++;
		}
		else if (!ft_isspace(*input))
		{
			data.next_command = 0;
			data.enc_and_or = false;
		}
		input++;
	}
	return (!data.next_command);
}
