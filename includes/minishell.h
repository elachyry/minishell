/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:57:48 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/12 20:02:54 by melachyr         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <fcntl.h>
# include "tokenizing.h"
#include  "../libraries/libft/libft.h"
# define READLINE_LIBRARY
// # include "/Users/akaddour/readline/include/readline/readline.h"
// # include "/Users/akaddour/readline/include/readline/history.h"
# include "/Users/melachyr/readline/readline.h"
# include "/Users/melachyr/readline/history.h"

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

typedef struct s_files
{
	t_token_type	type;
	char			*filename;
	t_bool			is_opened;
	struct s_files	*next;
}	t_files;

typedef struct	s_simple_cmd
{
	char	**cmd;
	char	*cmd_path;
	t_files	*files;
	int		is_first;
}	t_simple_cmd;

typedef struct s_shell_data
{
	char			*line;
	char			**environment;
	char			**path;
	int				status;
	int				nbr_cmd;
	t_token			*tokens;
	t_ast_node		*ast;
	t_simple_cmd	*simple_cmd;
	t_env			*environment_list;
}	t_shell_data;


extern t_shell_data g_shell_data;

const char	*get_token_type_name(t_token_type type);

//initialization
t_env	*initialize_environment_list(char **env);
char    *extract_key(char *env);
char    *extract_value(char *env);
void	extract_path(void);

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

//execution
void	execution(void);
t_bool	check_if_builtin(char *arg);
int 	execute_builtin(char **args);

//signals
void	handle_signals(void);

#endif