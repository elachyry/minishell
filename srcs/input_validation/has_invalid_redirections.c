/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_invalid_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:49:24 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/07 06:58:34 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	t_bool	helper(char *input, char sign2, int count)
{
	if (*input == sign2)
		return (false);
	if (count > 1)
		return (false);
	return (true);
}

t_bool	redirections_check(char *input, char sign, char sign2)
{
	t_bool	check;
	int		count;

	while (*input)
	{
		check = false;
		count = 0;
		if (*input == sign)
		{
			while (*(++input) == sign)
				count++;
			if (!helper(input, sign2, count))
				return (false);
			while (*input == ' ' || *input == sign)
			{
				check = true;
				input++;
			}
			if ((*input == sign && check == true) || *input == '\0'
				|| (*input == sign && *(input + 1) == '\0'))
				return (false);
		}
		input++;
	}
	return (true);
}

t_bool	has_invalid_redirections(char *input)
{
	return (redirections_check(input, '<', '>')
		&& redirections_check(input, '>', '<'));
}
