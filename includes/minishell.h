/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:57:48 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/23 14:59:50 by akaddour         ###   ########.fr       */
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
# include "../libraries/libft/libft.h"
# include "../libraries/get_next_line/get_next_line.h"
# define READLINE_LIBRARY
# include "/Users/akaddour/readline/include/readline/readline.h"
# include "/Users/akaddour/readline/include/readline/history.h"
// # include "/Users/melachyr/readline/readline.h"
// # include "/Users/melachyr/readline/history.h"

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

typedef struct s_simple_cmd
{
	char	**cmd;
	char	*cmd_path;
	char	*here_doc_path;
	int		nbr_here_doc;
	int		is_first;
	int		is_parenthis;
	int		is_parenthis_red_ch;
	t_bool	should_expand;
	t_files	*files;
}	t_simple_cmd;

typedef struct s_shell_data
{
	char			*line;
	char			**environment;
	char			**path;
	int				status;
	int				sig_exit;
	t_bool			ctl;
	t_token			*tokens;
	t_ast_node		*ast;
	t_simple_cmd	*simple_cmd;
	t_env			*environment_list;
}	t_shell_data;

extern t_shell_data	g_shell_data;

// expander_env_variable.c
typedef struct s_quote_state
{
	int	in_single_quotes;
	int	in_double_quotes;
	int	nested_quotes;
}	t_quote_state;

//  has_unclosed_parenthesis.c
typedef struct s_parenthesis_data
{
	int		open;
	char	prev_ns;
	t_bool	non_ws_enc;
	t_bool	after_cp;
	int		s_q_count;
	int		d_q_count;
}	t_parenthesis_data;

const char	*get_token_type_name(t_token_type type);

//initialization
t_env		*initialize_environment_list(char **env);
char		*extract_key(char *env);
char		*extract_value(char *env);
void		extract_path(void);

//builtins
int			ft_cd(char *path);
int			ft_echo(char **args);
int			ft_env(void);
int			ft_exit(char **args);
int			ft_export(char **args);
int			ft_pwd(void);
int			ft_unset(char **args);

//builtins_utils
void		update_env_value(char *key, char *value);
char		*get_env_value(char *key);
int			is_valid_key(char *key);
void		sort_env_array(t_env **env_array, int count);
void		handle_key_value(char *str, char *key, char *value);

//input_validation
t_bool		has_unclosed_parenthesis(char *input);
t_bool		has_unclosed_quotes(char *input);
t_bool		has_invalid_redirections(const char *input);
t_bool		has_misplaced_operators(const char *input);
t_bool		syntax_checker(char	*input);
t_bool		syntax_error_checker(char	*input);
t_bool		check_redirection_operator(const char **input, int *s_q_count, \
int *d_q_count, t_bool *encountered_and_or);
void		init_var(int *next_command, int *s_q_count, \
int *d_q_count, t_bool *enc_and_or);
t_bool		operator_mispla(const char **input, int *next_command, \
t_bool *enc_and_or, const char **temp);

// has_unclosed_parenthesis_utils.c
t_bool		handle_opening_parenthesis(int *open, \
char *prev_ns, t_bool *non_ws_enc);
t_bool		handle_close_par(char **input, int *open, \
t_bool *non_ws_enc, t_bool *after_cp);
t_bool		handle_after_closing_parenthesis(char **input, t_bool *after_cp);

// syntax_checker_utils.c
char		*handle_non_whitespace(char *result, char **tmp, int *l);
char		*epur_str(char *str);
t_bool		has_invalid_single_ampersand(const char *input);
t_bool		has_misplaced_operators_2(const char *input);
t_bool		has_invalid_redirections_2(const char *input);

int			is_invalid_operator(const char **input);
const char	*skip_spaces(const char *input);
void		update_quote_counts(char c, int *s_q_count, int *d_q_count);

//execution
t_ast_node	*extract_bash_cmd(t_token **tokens);
char		*ft_strjoin_2(char const *s1, char const *s2, size_t len);
void		execute_ast(t_ast_node *node);
void		execute_pipe(t_ast_node *node);
void		execute_logical_and(t_ast_node *node);
void		execute_logical_or(t_ast_node *node);
void		execute_less_than(t_ast_node *node);
void		execute_greater_than(t_ast_node *node);
void		execute_parenthesis(t_ast_node *ast);
void		execute_double_greater_than(t_ast_node *node);
char		*expand_here_doc(char *str);
t_files		*new_file_node(char *filename, t_token_type type);
void		add_lst_file(t_files **head, t_files *node);
t_files		*lst_file_last(t_files *head);
void		execute_here_doc(t_ast_node *node);
void		perror_message(char *file, int status);
int			get_cmd_path(char *args);
char		*get_here_doc_name(void);
void		redirect_files(void);
int			execute_command(char **args);
void		execution(void);
t_bool		check_if_builtin(char *arg);
int			execute_builtin(char **args);
void		less_than_operator(t_files *file);
void		greater_than_operator(t_files *file);
void		double_greater_than_operator(t_files *file);
void		sigquit_handler(int sig);
void		cmd_not_found(char **args, int status);
void		execve_fail(char **args);
int			redirect_files_buildin(void);
void		add_node_after(t_token *target_node, t_token *new_node);
t_ast_node	*cmd_before_red(t_token **tokens, t_token *ptr, t_bool is_parenth);
t_ast_node	*cmd_after_red(t_token **tokens, t_token *next, t_token *ptr);

// expander
t_token		*expand_tokens(t_token *tokens);
t_token		*expand_env_variable(t_token *tokens);
t_token		*expand_quotes(t_token *tokens);
t_token		*expand_wildcards(t_token *tokens);
char		*remove_all_quotes(t_token *token, char *str);

// expander_env_variable_utils.c
char		*fetch_variable_value(char **value, char *line, t_env *env);
char		*concatenate_char(char *str, char c);
char		*retrieve_env_var(char *name, t_env *env);

// expand_wildcards_utils.c
int			process_pattern(const char **string, const char **pattern, \
const char **str_backup, const char **pattern_backup);
int			match(const char *string, const char *pattern);
void		process_parenthesis(t_token **tok);
void		remove_quotes_and_advance(t_token **tok);
int			check_wildcard(t_token *tok, char **tmp);

//signals
void		handle_signals(void);

#endif