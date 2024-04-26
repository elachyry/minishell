/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:57:48 by melachyr          #+#    #+#             */
/*   Updated: 2024/04/25 17:17:02 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum	e_bool
{
	true = 1,
	false = 0,
} t_bool;



//libft
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);

//syntax_checker
t_bool	syntax_checker(char	*cmd);

# endif