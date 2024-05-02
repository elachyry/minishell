/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 02:33:51 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/02 02:53:42 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_environment_list(char *key, char *value)
{
	t_env *env_list;

	env_list = g_shell_data.environment_list;
	while (env_list)
	{
		if (!strcmp(key, env_list->key))
		{
			if (value)
				env_list->value = strdup(value);
			return ;
		}
		env_list = env_list->next;
	}
}

char	*get_environment_list_value(char *key)
{
	t_env *env_list;

	env_list = g_shell_data.environment_list;
	while (env_list)
	{
		if (!strcmp(key, env_list->key))
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

static	int	back_home(void)
{
	char	*home;

	update_environment_list("OLDPWD", get_environment_list_value("PWD"));
	home = get_environment_list_value("HOME");
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home) == 1)
		return (update_environment_list("PWD", home), 0);
	return (1);
}

static int display_cd_error_message(char *error_message) {
    ft_putstr_fd("minishell: cd: `", 2);
    ft_putstr_fd(error_message, 2);
    ft_putstr_fd("': No such file or directory\n", 2);
    return (1);
}

static int change_working_directory(void) {
    char *cwd;
	
	cwd = getcwd(NULL, 0);
    if (!cwd)
        return (1);
    return (update_environment_list("PWD", cwd), 0);
}

int	ft_cd(char *path)
{
	if (!path)
		return (back_home());
	if (chdir(path) != 1)
		return (display_cd_error_message(path));
	update_environment_list("OLDPWD", get_environment_list_value("PWD"));
	return (change_working_directory());
}