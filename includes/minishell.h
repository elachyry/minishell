/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:57:48 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/03 06:15:31 by akaddour         ###   ########.fr       */
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
# include "tokenizing.h"
# include <sys/ioctl.h>
# define READLINE_LIBRARY
# include "/Users/akaddour/readline/include/readline/readline.h"
# include "/Users/akaddour/readline/include/readline/history.h"
#include  "../libraries/libft/libft.h"

typedef enum e_bool
{
	true = 1,
	false = 0,
}	t_bool;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell_data
{
	char 	*line;
	char	**environment;
	t_token	*tokens;
	t_ast_node	*ast;
	t_env *environment_list;
}	t_shell_data;

extern t_shell_data g_shell_data;

//initialization
t_env	*initialize_environment_list(char **env);
char    *extract_key(char *env);
char    *extract_value(char *env);

//builtins
int		ft_cd(char *path);
int 	ft_echo(char **args);
int		ft_env(void);
void	ft_exit(char **args);
int		ft_export(char **args);
int 	ft_pwd(void);
int		ft_unset(char **args);

//builtins_utils
void	update_env_value(char *key, char *value);
char    *get_env_value(char *key);
int		is_valid_key(char *key);

//input_validation
t_bool	has_unclosed_parenthesis(char *input);
t_bool	has_unclosed_quotes(char *input);
t_bool	has_invalid_redirections(char *input);
t_bool	has_misplaced_operators(char *input);
t_bool	syntax_checker(char	*input);
t_bool	syntax_error_checker(char	*input);

//signals
void	handle_signals(void);

#endif