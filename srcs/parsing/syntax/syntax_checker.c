/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:50:49 by melachyr          #+#    #+#             */
/*   Updated: 2024/04/29 04:21:40 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_bool	syntax_error_checker(char	*input)
{
	char	*trimed;

	trimed = ft_strtrim(input, " \t\n\v\f\r");
	if (ft_strncmp(trimed, "", 1) == 0)
		return (false);
	if (!has_misplaced_operators(trimed)
		|| !has_invalid_redirections(trimed)
		|| !has_unclosed_quotes(trimed)
		|| !has_unclosed_parenthesis(trimed))
	{
		free(trimed);
		printf("syntax error\n");
		return (false);
	}
	return (true);
}
