/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:57:48 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/18 13:41:33 by melachyr         ###   ########.fr       */
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
# include <dirent.h>
# include <errno.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include "tokenizing.h"
#include  "../libraries/libft/libft.h"
#include  "../libraries/get_next_line/get_next_line.h"
# define READLINE_LIBRARY
// # include "/Users/akaddour/readline/include/readline/readline.h"
// # include "/Users/akaddour/readline/include/readline/history.h"
# include "/Users/melachyr/readline/readline.h"
# include "/Users/melachyr/readline/history.h"

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
	char	*here_doc_path;
	int		nbr_here_doc;
	int		is_first;
	int		is_parenthis;
	t_bool	should_expand;
	t_files	*files;
}	t_simple_cmd;

typedef struct s_shell_data
{
	char			*line;
	char			**environment;
	char			**path;
	int				status;
	t_bool			sig_exit;
	t_bool 			ctl;
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
int		ft_exit(char **args);
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
t_bool	has_invalid_redirections(const char *input);
t_bool	has_misplaced_operators(const char *input);
t_bool	syntax_checker(char	*input);
t_bool	syntax_error_checker(char	*input);

int	is_invalid_operator(const char **input);
const char	*skip_spaces(const char *input);
void	update_quote_counts(char c, int *s_q_count, int *d_q_count);

//execution
char	*ft_strjoin_2(char const *s1, char const *s2, size_t len);
void	execute_ast(t_ast_node *node);
void	execute_pipe(t_ast_node *node);
void	execute_logical_and(t_ast_node *node);
void	execute_logical_or(t_ast_node *node);
void	execute_less_than(t_ast_node *node);
void	execute_greater_than(t_ast_node *node);
void	execute_parenthesis(t_ast_node *ast);
void	execute_double_greater_than(t_ast_node *node);
char	*expand_here_doc(char *str, int fd);
t_files	*new_file_node(char *filename, t_token_type type);
void	add_lst_file(t_files **head, t_files *node);
t_files	*lst_file_last(t_files *head);
void	execute_here_doc(t_ast_node *node);
void	perror_message(char *file, int status);
int		get_cmd_path(char *args);
char	*get_here_doc_name();
void	redirect_files();
int 	execute_command(char **args);
void	execution(void);
t_bool	check_if_builtin(char *arg);
int 	execute_builtin(char **args);

//signals
void	handle_signals(void);

#endif