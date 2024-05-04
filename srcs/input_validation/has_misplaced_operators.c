/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_misplaced_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:41:36 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/03 04:19:37 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	has_misplaced_operators(char *input)
{
	t_bool	check;
	int		i;

	i = -1;
	while (input[++i])
	{
		check = false;
		if (input[0] == '|' || input[0] == '&')
			return (false);
		if (input[i] == '|')
		{
			while (input[i + 1] == ' ' || input[i + 1] == '\t')
			{
				check = true;
				i++;
			}
			if (input[i + 1] == '|' && check == true)
				return (false);
		}
		if (input[i] == '|' && input[i + 1] == '\0')
			return (false);
	}
	return (true);
}
