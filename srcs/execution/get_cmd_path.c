/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:36:12 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/16 20:18:01 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_entred_path(char *args, char *cmd)
{
	if (access(cmd, X_OK) != -1 || access(args, X_OK) != -1)
	{
		g_shell_data.simple_cmd->cmd_path = args;
		return (1);
	}
	else if (access(args, X_OK) == -1)
		return (2);
	return (0);
}

static int	search_for_cmd_path(char *args)
{
	char	*cmd;
	char	*path;
	char	*p;

	cmd = args;
	while (*g_shell_data.path)
	{
		path = ft_strjoin(*g_shell_data.path, "/");
		path = ft_strjoin(path, cmd);
		if (access(path, X_OK) != -1)
		{
			g_shell_data.simple_cmd->cmd_path = path;
			return (1);
		}
		free(path);
		g_shell_data.path++;
	}
	p = ft_strjoin("./", cmd);
	if (access(p, X_OK) != -1 && !g_shell_data.path[0])
	{
		g_shell_data.simple_cmd->cmd_path = cmd;
		return (1);
	}
	return (0);
}

int	get_cmd_path(char *args)
{
	char	*cmd;

	extract_path();
	cmd = ft_strrchr(args, '/');
	if (args[0] == '\0')
		return (0);
	else if (cmd)
		return (check_entred_path(args, cmd));
	else
		return (search_for_cmd_path(args));
	return (0);
}
