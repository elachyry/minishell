/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:30:23 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/03 06:00:50 by akaddour         ###   ########.fr       */
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
        printf("cd: HOME not set\n");
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
    if (!path)
        return (back_to_home());
    if (chdir(path) != 0)
    {
        display_cd_error(path);
        return (1);
    }
    update_env_value("OLDPWD", get_env_value("PWD"));
    update_env_value("PWD", getcwd(NULL, 0));
    return (0);
}