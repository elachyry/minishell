/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:30:23 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/23 13:26:57 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	back_to_home(void)
{
	char	*home;

	if (get_env_value("OLDPWD"))
		update_env_value("OLDPWD", getcwd(NULL, 0));
	home = get_env_value("HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) == 1)
	{
		update_env_value("PWD", home);
		return (0);
	}
	return (0);
}

static void	display_cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
}

int	ft_cd(char **path)
{
	char	*cwd;
	char	*oldpwd;

	if (path[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (!path[1] || (ft_strlen(path[1]) == 0 && get_env_value(path[1]) == NULL))
		return (back_to_home());
	if (chdir(path[1]) != 0)
	{
		display_cd_error(path[1]);
		return (1);
	}
	if (get_env_value("OLDPWD"))
		update_env_value("OLDPWD", oldpwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("minishell: cd: error retrieving current directory: \
		getcwd: cannot access parent directories: \
		No such file or directory\n", 2);
		return (1);
	}
	if (get_env_value("PWD"))
		update_env_value("PWD", cwd);
	return (0);
}
