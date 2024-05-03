/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:57:48 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/03 04:59:00 by akaddour         ###   ########.fr       */
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


// //libft
// char	*ft_strjoin(char *s1, char *s2);
// size_t	ft_strlen(const char *str);
// char	*ft_strtrim(char const *s1, char const *set);
// char	*ft_strrchr(const char *str, int c);
// char	*ft_strchr(const char *str, int c);
// size_t	ft_strlcpy(char *dst, const char *src, size_t size);
// char	**ft_split(char const *s, char sep);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	*ft_strdup(const char *s1);
// int		ft_strncmp(const char *str1, const char *str2, size_t n);
// char	*ft_strndup(const char *s1, size_t n);
// int		ft_strcmp(char *s1, char *s2);

//syntax_checker
t_bool	has_unclosed_parenthesis(char *input);
t_bool	has_unclosed_quotes(char *input);
t_bool	has_invalid_redirections(char *input);
t_bool	has_misplaced_operators(char *input);
t_bool	syntax_checker(char	*input);
t_bool	syntax_error_checker(char	*input);

void	handle_signals(void);
t_env	*initialize_environment_list(char **env);
char    *extract_key(char *env);
char    *extract_value(char *env);
void	update_env_value(char *key, char *value);
int		is_valid_key(char *key);
void	print_invalid_key_error(char *key);


int	ft_env(void);

#endif