/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_invalid_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:49:24 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/06 00:39:03 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_quote_counts(char c, int *s_q_count, int *d_q_count)
{
	if (c == 34)
		(*d_q_count)++;
	else if (c == 39)
		(*s_q_count)++;
}

const char	*skip_spaces(const char *input)
{
	while (*input && (*input == ' ' || *input == '\t'))
		input++;
	return (input);
}

int	is_invalid_operator(const char **input)
{
	const char *operator_start;
	int is_double_less_than;
	const char *temp_input = *input;

	operator_start = temp_input;
	is_double_less_than = (*operator_start == '<' && *(temp_input + 1) == '<');
	temp_input++;
	if (*operator_start == *temp_input && (*temp_input == '>' || *temp_input == '<'
			|| *temp_input == '|' || *temp_input == '&'))
		temp_input++;
	temp_input = skip_spaces(temp_input);
	if (*temp_input == '\0')
		return (1);
	if (*temp_input == '*' && !is_double_less_than)
		return (1);
	if (*temp_input == '>' || *temp_input == '<' || *temp_input == '|' || *temp_input == '&')
	{
		if (!(*operator_start == '|' || *operator_start == '&')
			|| !(*temp_input == '<' || *temp_input == '>'))
			return (1);
	}
	return (0);
}

t_bool	check_redirection_operator(const char **input, int *s_q_count, \
int *d_q_count, t_bool *encountered_and_or)
{
	const char	*temp;

	temp = *input;
	if (!(*s_q_count % 2) && !(*d_q_count % 2))
	{
		if (**input == '>' || **input == '<')
		{
			if (*temp == ')')
				return (false);
			if (is_invalid_operator(input))
				return (false);
		}
		else if (**input == '|' || **input == '&')
		{
			temp++;
			if (*temp == **input)
			{
				*encountered_and_or = true;
				*input += 2;
				return (true);
			}
		}
	}
	return (true);
}

t_bool	has_invalid_redirections(const char *input)
{
	int		s_q;
	int		d_q;
	t_bool	enc_and_or;

	s_q = 0;
	d_q = 0;
	enc_and_or = false;
	while (*input)
	{
		update_quote_counts(*input, &s_q, &d_q);
		if (!check_redirection_operator(&input, &s_q, &d_q, &enc_and_or))
			return (false);
		input++;
	}
	return (true);
}
