/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:50:49 by melachyr          #+#    #+#             */
/*   Updated: 2024/04/28 13:40:08 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_bool	syntax_error_checker(char	*input)
{
	char	*trimed;

	trimed = ft_strtrim(input, " \n\t");
	printf("quotes : %d\n", has_unclosed_quotes(trimed));
	printf("redirections : %d\n", has_invalid_redirections(trimed));
	printf("pipes : %d\n", has_misplaced_operators(trimed));
	printf("result : %d\n", has_misplaced_operators(trimed)
		&& has_invalid_redirections(trimed)
		&& has_unclosed_quotes(trimed));
	return (true);
}
