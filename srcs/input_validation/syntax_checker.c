/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:50:49 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/13 12:36:15 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool has_invalid_single_ampersand(const char *input) {
    int s_q_count = 0;
    int d_q_count = 0;
    while (*input) {
        update_quote_counts(*input, &s_q_count, &d_q_count);
        if (!(s_q_count % 2) && !(d_q_count % 2) && *input == '&') {
            const char *temp = input + 1;
            while (*temp == ' ' || *temp == '\t')
                temp++;
            if (*temp != '&' && *temp != '\0' && *(input - 1) != '&') // Ensure it's not followed by another '&'
                return (false); // Syntax error: single '&' character found outside quotes
        }
        input++;
    }
    return (true);
}

t_bool	syntax_error_checker(char	*input)
{
	// char	*trimed;

	g_shell_data.line = ft_strtrim(input, " \t\n\v\f\r");
	if (ft_strncmp(g_shell_data.line, "", 1) == 0)
		return (false);
	if (!has_misplaced_operators(g_shell_data.line)
		|| !has_invalid_redirections(g_shell_data.line)
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
