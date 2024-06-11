/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_invalid_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:49:24 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/11 23:09:33 by akaddour         ###   ########.fr       */
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
	const char	*operator_start;
	int			is_double_less_than;
	const char	*tmp;

	tmp = *input;
	operator_start = tmp;
	is_double_less_than = (*operator_start == '<' && *(tmp + 1) == '<');
	if (is_double_less_than)
		(*input)++;
	tmp++;
	if (*operator_start == *tmp && (*tmp == '>' || *tmp == '<'
			|| *tmp == '|' || *tmp == '&'))
		tmp++;
	tmp = skip_spaces(tmp);
	if (*tmp == '\0')
		return (1);
	if (*tmp == '*' && !is_double_less_than)
		return (1);
	if (*tmp == '>' || *tmp == '<' || *tmp == '|' || *tmp == '&')
	{
		if (!(*operator_start == '|' || *operator_start == '&')
			|| !(*tmp == '<' || *tmp == '>'))
			return (1);
	}
	return (0);
}

t_bool	check_redirection_operator(const char **input, int *s_q_count, \
int *d_q_count)
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
		if (!check_redirection_operator(&input, &s_q, &d_q))
			return (false);
		input++;
	}
	return (true);
}
