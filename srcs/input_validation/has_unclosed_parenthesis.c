/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_unclosed_parenthesis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 01:07:45 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/19 12:30:56 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_bool	has_unclosed_parenthesis(char *input)
// {
//     int		open;
//     char	prev;
//     t_bool	non_whitespace_encountered;

//     open = 0;
//     prev = 0;
//     non_whitespace_encountered = false;
//     while (*input)
//     {
//         if (*input == '(')
//         {
//             open++;
//             prev = '(';
//             non_whitespace_encountered = false;
//         }
//         else if (*input == ')')
//         {
//             if (open == 0 || prev == '(' || !non_whitespace_encountered)
//                 return (false);
//             open--;
//         }
//         else
//         {
//             prev = *input;
//             if (!ft_isspace(*input))
//                 non_whitespace_encountered = true;
//         }
//         input++;
//     }
//     if (open != 0)
//         return (false);
//     return (true);
// }

t_bool	has_unclosed_parenthesis(char *input)
{
    int		open;
    char	prev;
    char    prev_non_space;
    t_bool	non_whitespace_encountered;

    open = 0;
    prev = 0;
    prev_non_space = 0;
    non_whitespace_encountered = false;
    while (*input)
    {
        if (*input == '(')
        {
            // if (prev_non_space && !ft_isspace(prev_non_space) && prev_non_space != '|' && prev_non_space != '&')
            //     return false; // Return false if '(' is preceded by a non-space character that is not '|' or '&'
            open++;
            prev = '(';
            non_whitespace_encountered = false;
        }
        else if (*input == ')')
        {
            if (open == 0 || prev == '(' || !non_whitespace_encountered)
                return (false);
            open--;
        }
        else
        {
            prev = *input;
            if (!ft_isspace(*input))
            {
                non_whitespace_encountered = true;
                prev_non_space = *input;
            }
        }
        input++;
    }
    if (open != 0)
        return (false);
    return (true);
}