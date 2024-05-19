/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_invalid_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:49:24 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/19 20:50:27 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_quote_counts(char c, int *s_q_count, int *d_q_count)
{
	if (c == 34)
		(*d_q_count)++;
	else if (c == 39)
		(*s_q_count)++;
}

const char	*skip_spaces(const char *input)
{
	while (*input && (*input == ' ' || *input == '\t'))
		input++;
	return (input);
}

// int	is_invalid_operator(const char **input)
// {
//     const char	*operator_start;

//     operator_start = *input;
//     (*input)++;
//     if (*operator_start == **input && (**input == '>' || **input == '<' || **input == '|' || **input == '&'))
//         (*input)++;
//     *input = skip_spaces(*input);
//     if (**input == '\0')
//         return (1);
//     if (**input == '>' || **input == '<' || **input == '|' || **input == '&')
//     {
//         if (!(*operator_start == '|' || *operator_start == '&') || !(**input == '<' || **input == '>'))
//             return (1);
//     }
//     return (0);
// }

// int	is_invalid_operator(const char **input)
// {
//     const char	*operator_start;

//     operator_start = *input;
// 	printf("operator_start: %c\n", *operator_start);
//     (*input)++;
//     if (*operator_start == **input && (**input == '>' || **input == '<' || **input == '|' || **input == '&'))
//         (*input)++;
//     *input = skip_spaces(*input);
//     if (**input == '\0')
//         return (1);
//     if (**input == '>' || **input == '<')
//     {
//         if (*operator_start == '|' || *operator_start == '&')
//             return (0); // allow && or || before redirection
//         else
//             return (1);
//     }
//     return (0);
// }


int is_invalid_operator(const char **input) {
    const char *operator_start = *input;
    (*input)++;
    if (*operator_start == **input && (**input == '>' || **input == '<' || **input == '|' || **input == '&'))
        (*input)++;
    *input = skip_spaces(*input);
    if (**input == '\0')
        return (1);
    if (**input == '>' || **input == '<' || **input == '|' || **input == '&') {
        if (!(*operator_start == '|' || *operator_start == '&') || !(**input == '<' || **input == '>'))
            return (1);
    }
    return (0);
}


t_bool has_invalid_redirections(const char *input) {
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

// t_bool	has_invalid_redirections(const char *input)
// {
// 	int	s_q_count;
// 	int	d_q_count;

// 	s_q_count = 0;
// 	d_q_count = 0;
// 	while (*input)
// 	{
// 		update_quote_counts(*input, &s_q_count, &d_q_count);
// 		if ((!(s_q_count % 2) && !(d_q_count % 2))
// 			&& (*input == '>' || *input == '<'))
// 		{
// 			if (is_invalid_operator(&input))
// 				return (false);
// 		}
// 		else
// 			input++;
// 	}
// 	return (true);
// }