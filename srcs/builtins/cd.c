/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:30:23 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/14 22:11:09 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	back_to_home(void)
{
    char	*home;

    update_env_value("OLDPWD", get_env_value("PWD"));
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
    return (1);
}

static void display_cd_error(char *path)
{
    ft_putstr_fd("minishell: cd: `", 2);
    ft_putstr_fd(path, 2);
    ft_putstr_fd("': No such file or directory\n", 2);
}

int	ft_cd(char *path)
{
    char    *cwd;
    if (!path || (ft_strlen(path) == 0 && get_env_value(path) == NULL))
        return (back_to_home());
    if (chdir(path) != 0)
    {
        display_cd_error(path);
        return (1);
    }
    if (get_env_value("PWD"))
        update_env_value("OLDPWD", get_env_value("PWD"));
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
        return (1);
    }
    if (get_env_value("PWD"))
        update_env_value("PWD", cwd);
    return (0);
}


// not working segv
// cd "doesntexist" 2>/dev/null