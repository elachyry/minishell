/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:50:49 by melachyr          #+#    #+#             */
/*   Updated: 2024/04/26 22:46:48 by melachyr         ###   ########.fr       */
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


t_bool	has_invalid_redirections(char *cmd)
{
	t_bool	check;
	char	*cmdtrm;
	
	cmdtrm = ft_strtrim(cmd, " \t\n");
	while (*cmdtrm)
	{
		check = false;
		if (*cmdtrm == '<')
		{
			cmdtrm++;
			while (*cmdtrm == ' ' || *cmdtrm == '\t')
			{
				check = true;
				cmdtrm++;
			}
			if (*cmdtrm == '<' && check == true)
				return (false);
			if (*cmdtrm == '\0' || (*cmdtrm == '<' && *(cmdtrm + 1) == '\0'))
				return (false);

		}
		check = false;
		if (*cmdtrm == '>')
		{
			cmdtrm++;
			while (*cmdtrm == ' ' || *cmdtrm == '\t')
			{
				check = true;
				cmdtrm++;
			}
			if (*cmdtrm == '>' && check == true)
				return (false);
			if (*cmdtrm == '\0' || (*cmdtrm == '>' && *(cmdtrm + 1) == '\0'))
				return (false);
		}
		cmdtrm++;
	}
	return (true);
}
t_bool	has_misplaced_operators(char *cmd)
{
	char	*cmdtrm;
	t_bool	check;
	int		i;

	cmdtrm = ft_strtrim(cmd, " \t\n");
	i = -1;
	while (cmdtrm[++i])
	{
		check = false;
		if (cmdtrm[i] == '|' && i == 0)
		{
			// printf("1\n");
			return (false);
		}
		
		if (cmdtrm[i] == '|')
		{
			while (cmdtrm[i + 1] == ' ' || cmdtrm[i + 1] == '\t')
			{
				check = true;
				i++;
			}
			// printf("test %s\n", cmdtrm + i);
			if (cmdtrm[i + 1] == '|' && check == true)
			{
				// printf("3\n");
				return (false);
			}
		}
		if (cmdtrm[i] == '|' && cmdtrm[i + 1] == '\0')
		{
			// printf("2\n");
			return (false);
		}
	}
	return (true);
}

t_bool	syntax_checker(char	*cmd)
{
	printf("quotes : %d\n", has_unclosed_quotes(cmd));
	printf("redirections : %d\n", has_invalid_redirections(cmd));
	printf("pipes : %d\n", has_misplaced_operators(cmd));
	printf("result : %d\n", has_misplaced_operators(cmd) && has_invalid_redirections(cmd) && has_unclosed_quotes(cmd));
	return (0);
}
