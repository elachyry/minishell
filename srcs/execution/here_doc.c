/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:28:30 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/14 02:02:10 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	help_function(t_ast_node *node);

static void	here_doc(char **cmd, char **content)
{
	char	*str;
	char	*buff;
	char	*delimiter;

	str = NULL;
	delimiter = cmd[0];
	buff = ft_strdup("");
	while (1)
	{
		str = readline("> ");
		if (str)
		{
			if (write_in_file(str, delimiter, &buff, content))
				break ;
		}
		else
		{
			*content = ft_strdup(buff);
			break ;
		}
	}
}

static void	handle_here_doc(t_ast_node *node)
{
	char	*content;

	help_function(node->left);
	if (ft_strchr(node->right->args[0], '\'') || ft_strchr(node->right->args[0], '\"'))
		g_shell_data.simple_cmd->should_expand = false;
	expand_quotes(node->right->args);
	here_doc(node->right->args, &content);
	write_content_to_file(content, node->right->args[1]);
	help_function(node->right->right);
}

void	extrac_ast_parenth(t_ast_node *node)
{
	char		*line;
	t_token		*tokens;

	if (!node)
		return ;
	else if (node->type == OpeningParenthesis)
	{
		line = concat_cmd(node);
		tokens = ft_tokenize(line);
		tokens = expand_tokens(tokens);
		g_shell_data.ast_parenth
		[g_shell_data.simple_cmd->parenth_index] = parse_tokens(&tokens);
		g_shell_data.simple_cmd->parenth_index++;
	}
	else if (node->type >= 0 && node->type <= 7)
	{
		extrac_ast_parenth(node->left);
		extrac_ast_parenth(node->right);
	}
}

void	help_function(t_ast_node *node)
{
	if (!node)
		return ;
	else if (node->type == OpeningParenthesis)
	{
		help_function(g_shell_data.ast_parenth
		[g_shell_data.simple_cmd->parenth_index]);
		g_shell_data.simple_cmd->parenth_index++;
	}
	else if (node->type == PipeSymbol
		|| node->type == LogicalAnd
		|| node->type == LogicalOr
		|| node->type == LessThanOperator
		|| node->type == GreaterThanOperator
		|| node->type == DoubleGreaterThanOperator
		|| node->type == IDENTIFIER)
	{
		help_function(node->left);
		help_function(node->right);
	}
	else if (node->type == DoubleLessThanOperator)
		handle_here_doc(node);
}

void	execute_here_doc(t_ast_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror_message("fork", EXIT_FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, sigint_herdoc_handler);
		if (!node)
			return ;
		help_function(node);
		gc_cleanup();
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, NULL, 0);
}
