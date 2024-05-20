/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:50:49 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/20 11:25:17 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*epur_str(char *str)
{
	int		i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	char *tmp = str + i;
	i = 0;
	char *result = ft_strdup("");
	int	j = 0;
	int	l = 0;
	while (tmp[i] != '\0')
	{
		l = 0;
		if (tmp[i] < 9 || tmp[i] > 13)
		{
			if (!(ft_isspace(tmp[i]) && i == (int)ft_strlen(tmp) - 1))
			{
				if (!ft_isspace(tmp[i]))
					result = ft_strjoin_2(result, tmp + i, 1);
			}
			while (ft_isspace(tmp[i]) && tmp[i] != '\0')
			{	
				i++;
				l = 1;
			}
			j++;
		}
		if (l == 0)
			i++;
	}
	// printf("result %s\n", result);
	return (result);
}


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


t_bool has_misplaced_operators_2(const char *input) {
    int expect_command_next = 0;
    int s_q_count = 0;
    int d_q_count = 0;
    t_bool encountered_and_or = false;

    if (*input == '|' || *input == '&')
        return false;
    while (*input) {
        update_quote_counts(*input, &s_q_count, &d_q_count);
        if (!(s_q_count % 2) && !(d_q_count % 2) && (*input == '|' || *input == '&')){
			if (*(input + 1) == ')' || *(input - 1) == '(')
				return (false);
            if (!encountered_and_or) {
                encountered_and_or = true;
                const char *temp = input;
                temp++;
                if (*temp == *input) {
                    temp++;
                    if (*temp == *input) {
                        return false; // Return false if there are three consecutive | or & characters
                    }
                    input++;
                    continue;
                }
            }
            if (expect_command_next)
                return false;
            expect_command_next = 1;
        } else if (!ft_isspace(*input)) {
            expect_command_next = 0;
            encountered_and_or = false;
        }
        input++;
    }
    if (expect_command_next)
        return false;
    return true;
}

t_bool has_invalid_redirections_2(const char *input) {
    int s_q_count = 0;
    int d_q_count = 0;
    t_bool encountered_and_or = false;
    while (*input) {
        update_quote_counts(*input, &s_q_count, &d_q_count);
        if (!(s_q_count % 2) && !(d_q_count % 2) && (*input == '>' || *input == '<'))
		{
			if (*(input + 1) == ')')
				return (false);
            if (is_invalid_operator(&input))
                return false;
        } else if (!encountered_and_or && !(s_q_count % 2) && !(d_q_count % 2) && (*input == '|' || *input == '&')) {
            const char *temp = input;
            temp++;
            if (*temp == *input) {
                encountered_and_or = true;
                input += 2;
                continue;
            }
        }
        input++;
    }
    return true;
}


t_bool	syntax_error_checker(char	*input)
{
	// char	*trimed;

	g_shell_data.line = ft_strtrim(input, " \t\n\v\f\r");
	char *str = epur_str(g_shell_data.line);
	if (ft_strncmp(g_shell_data.line, "", 1) == 0)
		return (false);
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
