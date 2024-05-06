/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_misplaced_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:41:36 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/06 10:48:20 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	handle_logical_or(char *input)
{
	t_bool	check;
	int		count;
	int		i;

	i = -1;
	while (input[++i])
	{
		count = 0;
		check = false;
		if (input[i] == '|' && i == 0)
			return (false);
		if (input[i] == '|')
		{
			if (input[i - 1] == '&' || input[i - 1] == '(' || input[i - 1] == ')')
				return (false);
			while (input[i] == '|')
			{
				count++;
				i++;
			}
			if (count > 2)
				return (false);
			if (input[i] == '\0')
				return (false);
			while (input[i + 1] == ' ' || input[i + 1] == '\t')
			{
				check = true;
				i++;
			}
			if (input[i] == '&')
				return (false);
			if (input[i + 1] == '|' && check == true)
				return (false);
		}
		if (input[i] == '|' && input[i + 1] == '\0')
			return (false);
	}
	return (true);
}

t_bool	handle_logical_and(char *input)
{
	t_bool	check;
	int		count;
	int		i;

	i = -1;
	while (input[++i])
	{
		check = false;
		count = 0;
		if (input[i] == '&' && i == 0)
			return (false);
		if (input[i] == '&')
		{
			if (input[i - 1] == '|' || input[i - 1] == '(' || input[i - 1] == ')')
				return (false);
			while (input[i] == '&')
			{
				count++;
				i++;
			}
			if (count > 2)
				return (false);
			if (input[i] == '\0')
				return (false);
			while (input[i] == ' ' || input[i] == '\t')
			{
				check = true;
				i++;
			}
			if (input[i] == '|')
				return (false);
			if (input[i] == '&' && check == true)
				return (false);
		}
		if (input[i] == '&' && input[i + 1] == '\0')
			return (false);
	}
	return (true);
}

t_bool	has_misplaced_operators(char *input)
{
	return (handle_logical_or(input) && handle_logical_and(input));
}
