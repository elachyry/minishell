/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:50:49 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/11 14:07:12 by melachyr         ###   ########.fr       */
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
	if (!has_misplaced_operators(str)
		|| !has_misplaced_operators_2(g_shell_data.line)
		|| !has_invalid_redirections(str)
		|| !has_invalid_redirections_2(g_shell_data.line)
		|| !has_unclosed_quotes(g_shell_data.line)
		|| !has_unclosed_parenthesis(g_shell_data.line)
		|| !has_invalid_single_ampersand(g_shell_data.line))
	{
		printf("syntax error\n");
		return (false);
	}
	return (true);
}
