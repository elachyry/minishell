/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:50:49 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/29 21:06:27 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	syntax_error_checker(char	*input)
{
	char	*str;

	g_shell_data.line = ft_strtrim(input, " \t\n\v\f\r");
	str = epur_str(g_shell_data.line);
	if (ft_strncmp(g_shell_data.line, "", 1) == 0)
		return (true);
	// int res1 = has_misplaced_operators(str);
	// int res2 = has_misplaced_operators_2(g_shell_data.line);
	// int res3 = has_invalid_redirections(str);
	// int res4 = has_invalid_redirections_2(g_shell_data.line);
	// int res5 = has_unclosed_quotes(g_shell_data.line);
	// int res6 = has_unclosed_parenthesis(g_shell_data.line);
	// int res7 = has_invalid_single_ampersand(g_shell_data.line);
	// printf("res1: %d\n", res1);
	// printf("res2: %d\n", res2);
	// printf("res3: %d\n", res3);
	// printf("res4: %d\n", res4);
	// printf("res5: %d\n", res5);
	// printf("res6: %d\n", res6);
	// printf("res7: %d\n", res7);
	if (!has_misplaced_operators(str)
		|| !has_misplaced_operators_2(g_shell_data.line)
		|| !has_invalid_redirections(str)
		|| !has_invalid_redirections_2(g_shell_data.line)
		|| !has_unclosed_quotes(g_shell_data.line)
		|| !has_unclosed_parenthesis(g_shell_data.line)
		|| !has_invalid_single_ampersand(g_shell_data.line))
	{
		free(g_shell_data.line);
		printf("syntax error\n");
		return (false);
	}
	return (true);
}
