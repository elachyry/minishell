/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_misplaced_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:41:36 by melachyr          #+#    #+#             */
/*   Updated: 2024/04/28 13:40:08 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_bool	has_misplaced_operators(char *input)
{
	t_bool	check;
	int		i;

	i = -1;
	while (input[++i])
	{
		check = false;
		if (input[i] == '|' && i == 0)
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
