/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_unclosed_parenthesis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 01:07:45 by akaddour          #+#    #+#             */
/*   Updated: 2024/04/29 06:45:43 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_bool	has_unclosed_parenthesis(char *input)
{
	int		open;
	int		close;

	open = 0;
	close = 0;
	while (*input)
	{
		if (*input == '(')
			open++;
		if (*input == ')')
			close++;
		input++;
	}
	if (open != close)
		return (false);
	return (true);
}
