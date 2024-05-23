/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_misplaced_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:41:36 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/21 22:37:03 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_var(int *next_command, int *s_q_count, \
int *d_q_count, t_bool *enc_and_or)
{
	*next_command = 0;
	*s_q_count = 0;
	*d_q_count = 0;
	*enc_and_or = false;
}

t_bool	operator_mispla(const char **input, int *next_command, \
t_bool *enc_and_or, const char **temp)
{
	if (*(*input + 1) == ')' || *(*input - 1) == '(')
		return (true);
	if (!*enc_and_or)
	{
		*enc_and_or = true;
		*temp = *input + 1;
		if (**temp == **input)
		{
			(*temp)++;
			if (**temp == **input)
				return (true);
			(*input)++;
		}
		else if (*next_command)
			return (true);
		else
			*next_command = 1;
	}
	else if (*next_command)
		return (true);
	return (false);
}

t_bool	has_misplaced_operators(const char *input)
{
	int			next_command;
	int			s_q;
	int			d_q;
	t_bool		enc_and_or;
	const char	*temp;

	init_var(&next_command, &s_q, &d_q, &enc_and_or);
	if (*input == '|' || *input == '&')
		return (false);
	while (*input)
	{
		update_quote_counts(*input, &s_q, &d_q);
		if (!(s_q % 2) && !(d_q % 2) && (*input == '|' || *input == '&'))
		{
			if (operator_mispla(&input, &next_command, &enc_and_or, &temp))
				return (false);
		}
		else if (!ft_isspace(*input))
		{
			next_command = 0;
			enc_and_or = false;
		}
		input++;
	}
	return (!next_command);
}
