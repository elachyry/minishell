/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:36:12 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/02 18:34:13 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_entred_path(char *args)
{
	if (access(args, X_OK) != -1)
	{
		g_shell_data.simple_cmd->cmd_path = args;
		return (1);
	}
	else if (access(args, X_OK) == -1 && access(args, F_OK) != -1)
		return (2);
	else if (access(args, X_OK) == -1)
		return (3);
	return (0);
}

static int	search_for_cmd_path(char *args)
{
	char	*cmd;
	char	*path;
	char	*p;
	int		i;

	cmd = args;
	i = -1;
	while (g_shell_data.path[++i])
	{
		path = ft_strjoin(g_shell_data.path[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, X_OK) != -1)
		{
			g_shell_data.simple_cmd->cmd_path = path;
			return (1);
		}
	}
	p = ft_strjoin("./", cmd);
	if (access(p, X_OK) != -1 && g_shell_data.path[0] == NULL)
	{
		g_shell_data.simple_cmd->cmd_path = cmd;
		return (1);
	}
	return (0);
}

int	get_cmd_path(char *args)
{
	char	*cmd;

	if (!args)
		return (4);
	extract_path();
	cmd = ft_strrchr(args, '/');
	if (args[0] == '\0')
		return (0);
	else if (cmd)
		return (check_entred_path(args));
	else
		return (search_for_cmd_path(args));
	return (0);
}
