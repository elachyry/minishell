/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:50:49 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/24 19:04:47 by akaddour         ###   ########.fr       */
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
	// t_bool ret = has_misplaced_operators(str);
	// t_bool ret2 = has_misplaced_operators_2(g_shell_data.line);
	// t_bool ret3 = has_invalid_redirections(str);
	// t_bool ret4 = has_invalid_redirections_2(g_shell_data.line);
	// t_bool ret5 = has_unclosed_quotes(g_shell_data.line);
	// t_bool ret6 = has_unclosed_parenthesis(g_shell_data.line);
	// t_bool ret7 = has_invalid_single_ampersand(g_shell_data.line);
	// printf("ret: %d\n", ret);
	// printf("ret2: %d\n", ret2);
	// printf("ret3: %d\n", ret3);
	// printf("ret4: %d\n", ret4);
	// printf("ret5: %d\n", ret5);
	// printf("ret6: %d\n", ret6);
	// printf("ret7: %d\n", ret7);
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
