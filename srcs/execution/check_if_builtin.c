// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   check_if_builtin.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/07 08:13:08 by akaddour          #+#    #+#             */
// /*   Updated: 2024/05/07 10:11:56 by melachyr         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// int execute_builtin(char **args)
// {
//     if (!ft_strcmp(args[0], "echo"))
//         return (ft_echo(args));
//     if (!ft_strcmp(args[0], "cd"))
//         return (ft_cd(args));
//     if (!ft_strcmp(args[0], "pwd"))
//         return (ft_pwd());
//     if (!ft_strcmp(args[0], "export"))
//         return (ft_export(args));
//     if (!ft_strcmp(args[0], "unset"))
//         return (ft_unset(args));
//     if (!ft_strcmp(args[0], "env"))
//         return (ft_env());
// 	ft_exit(args);
//     return (0);
// }

// t_bool	check_if_builtin(char *arg)
// {
//     if (!ft_strcmp(arg, "echo"))
//         return (true);
//     if (!ft_strcmp(arg, "cd"))
//         return (true);
//     if (!ft_strcmp(arg, "pwd"))
//         return (true);
//     if (!ft_strcmp(arg, "export"))
//         return (true);
//     if (!ft_strcmp(arg, "unset"))
//         return (true);
//     if (!ft_strcmp(arg, "env"))
//         return (true); 
//     if (!ft_strcmp(arg, "exit"))
//         return (true);
//     return (false);
// }