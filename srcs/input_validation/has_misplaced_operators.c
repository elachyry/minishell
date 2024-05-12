/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_misplaced_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:41:36 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/12 15:52:35 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_bool	handle_logical_or(char *input)
// {
// 	t_bool	check;
// 	int		count;
// 	int		i;

// 	i = -1;
// 	while (input[++i])
// 	{
// 		count = 0;
// 		check = false;
// 		if (input[i] == '|' && i == 0)
// 			return (false);
// 		if (input[i] == '|')
// 		{
// 			if (input[i - 1] == '&' || input[i - 1] == '(' || input[i - 1] == ')')
// 				return (false);
// 			while (input[i] == '|')
// 			{
// 				count++;
// 				i++;
// 			}
// 			if (count > 2 || (count == 2 && input[i] == '|'))
//                 return (false);
// 			if (input[i] == '\0')
// 				return (false);
// 			while (input[i + 1] == ' ' || input[i + 1] == '\t')
// 			{
// 				check = true;
// 				i++;
// 			}
// 			if (input[i] == '&')
// 				return (false);
// 			if ((input[i] == '|' && check == true) || (input[i] == '|' && input[i + 1] == '|'))
//                 return (false);
// 		}
// 		if (input[i] == '|' && input[i + 1] == '\0')
// 			return (false);
// 	}
// 	return (true);
// }

// t_bool	handle_logical_and(char *input)
// {
// 	t_bool	check;
// 	int		count;
// 	int		i;

// 	i = -1;
// 	while (input[++i])
// 	{
// 		check = false;
// 		count = 0;
// 		if (input[i] == '&' && i == 0)
// 			return (false);
// 		if (input[i] == '&')
// 		{
// 			if (input[i - 1] == '|' || input[i - 1] == '(' || input[i - 1] == ')')
// 				return (false);
// 			while (input[i] == '&')
// 			{
// 				count++;
// 				i++;
// 			}
// 			if (count > 2 || (count == 2 && input[i] == '&'))
// 				return (false);
// 			if (input[i] == '\0')
// 				return (false);
// 			while (input[i] == ' ' || input[i] == '\t')
// 			{
// 				check = true;
// 				i++;
// 			}
// 			if (input[i] == '|')
// 				return (false);
// 			if ((input[i] == '&' && check == true) || (input[i] == '&' && input[i + 1] == '&'))
// 				return (false);
// 		}
// 		if (input[i] == '&' && input[i + 1] == '\0')
// 			return (false);
// 	}
// 	return (true);
// }

// t_bool	has_misplaced_operators(char *input)
// {
// 	return (handle_logical_or(input) && handle_logical_and(input));
// }



// t_bool	has_misplaced_operators(const char *input)
// {
// 	int	expect_command_next;
// 	int	s_q_count;
// 	int	d_q_count;

// 	s_q_count = 0;
// 	d_q_count = 0;
// 	expect_command_next = 0;
// 	if (*input == '|' || *input == '&')
// 		return (false);
// 	while (*input)
// 	{
// 		update_quote_counts(*input, &s_q_count, &d_q_count);
// 		if ((*input == '|' || *input == '&') && !(s_q_count % 2) && !(d_q_count % 2))
//         {
//             if (expect_command_next)
//                 return (false);
//             expect_command_next = 1;
//         }
// 		else if (!ft_isspace(*input))
// 			expect_command_next = 0;
// 		input++;
// 	}
// 	if (expect_command_next)
// 		return (false);
// 	return (true);
// }

t_bool	has_misplaced_operators(const char *input)
{
	int  single_quote_count;
	int  double_quote_count;
	t_bool  expect_command_next;

	single_quote_count = 0;
	double_quote_count = 0;
	expect_command_next = false;
	while (*input)
	{
		if (*input == 34)
			double_quote_count++;
		else if (*input == 39)
			single_quote_count++;
		if ((*input == '|' || *input == '&') && !(single_quote_count % 2) && !(double_quote_count % 2))
		{
			if (expect_command_next)
				return (false);
			expect_command_next = false;
		}
		else if (!ft_isspace(*input))
			expect_command_next = true;
		input++;
	}
	return (!expect_command_next);
}