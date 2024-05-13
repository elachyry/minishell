/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_invalid_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:49:24 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/13 12:58:02 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static	t_bool	helper(char *input, char sign2, int count)
// {
// 	if (*input == sign2)
// 		return (false);
// 	if (count > 1)
// 		return (false);
// 	return (true);
// }

// t_bool	redirections_check(char *input, char sign, char sign2)
// {
// 	t_bool	check;
// 	int		count;

// 	while (*input)
// 	{
// 		check = false;
// 		count = 0;
// 		if (*input == sign)
// 		{
// 			while (*(++input) == sign)
// 				count++;
// 			if (!helper(input, sign2, count))
// 				return (false);
// 			while (*input == ' ' || *input == sign)
// 			{
// 				check = true;
// 				input++;
// 			}
// 			if ((*input == sign && check == true) || *input == '\0'
//                 || (*input == sign && *(input + 1) == '\0')
//                 || *input == '|' || *input == '&')
//                 return (false);
// 		}
// 		input++;
// 	}
// 	return (true);
// }


// t_bool	has_invalid_redirections(char *input)
// {
// 	return (redirections_check(input, '<', '>')
// 		&& redirections_check(input, '>', '<'));
// }




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

int	is_invalid_operator(const char **input)
{
    const char	*operator_start;

    operator_start = *input;
    (*input)++;
    if (*operator_start == **input && (**input == '>' || **input == '<' || **input == '|' || **input == '&'))
        (*input)++;
    *input = skip_spaces(*input);
    if (**input == '\0')
        return (1);
    if (**input == '>' || **input == '<' || **input == '|' || **input == '&')
    {
        if (!(*operator_start == '|' || *operator_start == '&') || !(**input == '<' || **input == '>'))
            return (1);
    }
    return (0);
}

t_bool	has_invalid_redirections(const char *input)
{
	int	s_q_count;
	int	d_q_count;

	s_q_count = 0;
	d_q_count = 0;
	while (*input)
	{
		update_quote_counts(*input, &s_q_count, &d_q_count);
		if ((!(s_q_count % 2) && !(d_q_count % 2))
			&& (*input == '>' || *input == '<'))
		{
			if (is_invalid_operator(&input))
				return (false);
		}
		else
			input++;
	}
	return (true);
}