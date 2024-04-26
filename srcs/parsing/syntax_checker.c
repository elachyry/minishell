/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:50:49 by melachyr          #+#    #+#             */
/*   Updated: 2024/04/26 10:12:19 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_bool	syntax_error_checker(char *cmd)
// {
	
// }


t_bool	has_unclosed_quotes(char *cmd)
{
	int	dquot;
	int	squot;

	dquot = 0;
	squot = 0;
	while (*cmd)
	{
		if (*cmd == '\'')
		{
			squot++;
			cmd++;
			while (*cmd)
			{
				if (*cmd == '\'')
				{
					squot++;
					cmd++;
					break ;
				}
				cmd++;
			}
			if (squot % 2 == 0)
				continue ;
			return (false);
		}
		if (*cmd == '\"')
		{
			dquot++;
			cmd++;
			while (*cmd)
			{
				if (*cmd == '\"')
				{
					dquot++;
					cmd++;
					break ;
				}
				cmd++;
			}
			if (dquot % 2 == 0)
				continue ;
			return (false);
		}
		cmd++;
	}
	return (true);
}

// t_bool	has_invalid_redirections(char *cmd)
// {
	
// 	return (true);
// }

t_bool	syntax_checker(char	*cmd)
{
	printf("result : %d\n", has_unclosed_quotes(cmd));
	return (0);
}
