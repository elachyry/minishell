/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_unclosed_parenthesis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 01:07:45 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/05 07:08:30 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	has_unclosed_parenthesis(char *input)
{
    int		open;
    char	prev;
    t_bool	non_whitespace_encountered;

    open = 0;
    prev = 0;
    non_whitespace_encountered = false;
    while (*input)
    {
        if (*input == '(')
        {
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
                non_whitespace_encountered = true;
        }
        input++;
    }
    if (open != 0)
        return (false);
    return (true);
}