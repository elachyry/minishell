/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_unclosed_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:02:59 by melachyr          #+#    #+#             */
/*   Updated: 2024/04/28 13:40:08 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_quotes(char **input_ptr, int *counter, char type)
{
	(*counter)++;
	(*input_ptr)++;
	while (**input_ptr)
	{
		if (**input_ptr == type)
		{
			(*counter)++;
			(*input_ptr)++;
			break ;
		}
		(*input_ptr)++;
	}
}

t_bool	has_unclosed_quotes(char *input)
{
	int	dquot;
	int	squot;

	dquot = 0;
	squot = 0;
	while (*input)
	{
		if (*input == '\'')
		{
			handle_quotes(&input, &squot, '\'');
			if (squot % 2 == 0)
				continue ;
			return (false);
		}
		if (*input == '\"')
		{
			handle_quotes(&input, &dquot, '\"');
			if (dquot % 2 == 0)
				continue ;
			return (false);
		}
		input++;
	}
	return (true);
}
