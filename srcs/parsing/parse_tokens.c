/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:37:53 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/14 09:52:39 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*new_ast_node(t_token_type type)
{
	t_ast_node	*node;
	
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

t_ast_node	*new_ast_file_node(t_token *token)
{
	t_ast_node	*node;

	if (token == NULL)
		return (NULL);
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
		return (NULL);
	node->args[0] = token->value;
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*parse_command(t_token	**tokens)
{
	int			count;
	int			i;
	char		**cmd;
	t_token		*ptr;
	t_ast_node	*node;

	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	// printf("parse_command token = %s\n", (*tokens)->value);
	ptr = *tokens;
	count = 0;
	while (ptr && ptr->type == IDENTIFIER)
	{
		count++;
		ptr = ptr->next;
	}
	// dprintf(2, "count %d\n", count);
	cmd = malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return (NULL);
	ptr = *tokens;
	i = -1;
	while (++i < count)
	{
		cmd[i] = ptr->value;
		ptr = ptr->next;
	}
	cmd[i] = NULL;
	*tokens = ptr;
	node = malloc(sizeof(t_ast_node));
	node->args = cmd;
	node->type = IDENTIFIER;
	node->left = NULL;
	// printf("parse_command2 token = %s\n", *tokens == NULL ? "NULL" : (*tokens)->value);
	node->right = parse_redirection(tokens);
	// for (int i = 0; cmd[i] != NULL; i++)
	// 	dprintf(2, "%s\n", cmd[i]);
	// g_shell_data.nbr_cmd++;
	
	return (node);
}
t_ast_node	*parse_command_with_sepa_arg(t_token *tokens, t_token *args)
{
	int			count;
	int			count2;
	int			i;
	char		**cmd;
	t_token		*ptr;
	t_token		*ptr2;
	t_ast_node	*node;

	if (tokens == NULL || tokens == NULL)
		return (NULL);
	// printf("parse_command token = %s\n", (*tokens)->value);
	ptr = tokens;
	count = 0;
	while (ptr && ptr->type == IDENTIFIER)
	{
		count++;
		ptr = ptr->next;
	}
	ptr2 = args;
	count2 = 0;
	while (ptr2 && ptr2->type == IDENTIFIER)
	{
		count2++;
		ptr2 = ptr2->next;
	}
	// dprintf(2, "count %d count2 %d\n", count, count2);
	cmd = malloc(sizeof(char *) * (count + count2 + 1));
	if (!cmd)
		return (NULL);
	ptr = tokens;
	i = -1;
	while (++i < count)
	{
		cmd[i] = ptr->value;
		ptr = ptr->next;
	}
	ptr2 = args;
	int	j = -1;
	while (++j < count2)
	{
		cmd[i] = ptr2->value;
		ptr2 = ptr2->next;
		i++;
	}
	cmd[i] = NULL;
	tokens = ptr;
	node = malloc(sizeof(t_ast_node));
	node->args = cmd;
	node->type = IDENTIFIER;
	node->left = NULL;
	node->right = NULL;
	// for (int i = 0; cmd[i] != NULL; i++)
	// 	dprintf(2, "%s\n", cmd[i]);
	// g_shell_data.nbr_cmd++;
	
	return (node);
}

t_ast_node	*parse_custom_command(t_token *token)
{
	t_ast_node	*node;

	if (token == NULL)
		return (NULL);
	// printf("parse_custom_command\n");
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
		return (NULL);
	node->args[0] = token->value;
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	g_shell_data.nbr_cmd++;
	return (node);
}


t_ast_node	*parse_redirection(t_token **tokens)
{
	t_ast_node	*redirection_node;
	t_token		*ptr;
	t_token		*next;

	if (!tokens || !*tokens)
		return (NULL);
	ptr = *tokens;
	if ((*tokens)->type == LessThanOperator || (*tokens)->type == DoubleLessThanOperator
		|| (*tokens)->type == GreaterThanOperator || (*tokens)->type == DoubleGreaterThanOperator)
	{
		// dprintf(2, "1 %s\n", (*tokens)->value);
		if ((*tokens)->type == DoubleLessThanOperator)
			g_shell_data.simple_cmd->nbr_here_doc++;
		redirection_node = new_ast_node((*tokens)->type);
		*tokens = NULL;
		redirection_node->left = parse_redirection(tokens);
		// dprintf(2, "2 %s\n", ptr->next->next == NULL ? "NULL" :  ptr->next->next->value);
		if (redirection_node->left == NULL && ptr->next->next && ptr->next->next->type == IDENTIFIER)
			redirection_node->left = parse_custom_command(ptr->next->next);
		// dprintf(2, "3 %s\n", ptr->next->value);
		redirection_node->right = parse_command(&ptr->next);
		return (redirection_node);
	}
	while (*tokens && (*tokens)->next)
	{
		next = (*tokens)->next;
		if (next->type == LessThanOperator || next->type == DoubleLessThanOperator
			|| next->type == GreaterThanOperator || next->type == DoubleGreaterThanOperator)
		{
			// printf("red = %s\n", next->value);
			if (next->type == DoubleLessThanOperator)
				g_shell_data.simple_cmd->nbr_here_doc++;
			redirection_node = new_ast_node(next->type); 
			(*tokens)->next = NULL;
			if (next->next->next && next->next->next->type == IDENTIFIER)
			{
				// printf("yesy\n");
				redirection_node->left = parse_command_with_sepa_arg(ptr, next->next->next);
			}
			else
				redirection_node->left = parse_redirection(&ptr);
			redirection_node->right = parse_command(&next->next);
			return (redirection_node);
		}
		*tokens = next;
	}
    return (parse_command(&ptr));
}


t_ast_node	*parse_parenthese(t_token **tokens)
{
	t_token		*next;
	t_token		*ptr;
	
	ptr = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next = *tokens;
		if (next->type == OpeningParenthesis)
		{
			int			count;
			int			i;
			char		**cmd;
			t_token		*tmp;
			t_ast_node	*node;

			tmp = (*tokens)->next;
			while (tmp && tmp->type == OpeningParenthesis)
				tmp = tmp->next;
			count = 0;
			while (tmp && tmp->type != ClosingParenthesis)
			{
				count++;
				tmp = tmp->next;
			}
			cmd = malloc(sizeof(char *) * (count + 1));
			if (!cmd)
				return (NULL);
			tmp = (*tokens)->next;
			while (tmp && tmp->type == OpeningParenthesis)
				tmp = tmp->next;
			i = -1;
			while (++i < count)
			{
				cmd[i] = tmp->value;
				tmp = tmp->next;
			}
			cmd[i] = NULL;
			*tokens = tmp;
			node = malloc(sizeof(t_ast_node));
			node->args = cmd;
			node->type = OpeningParenthesis;
			node->left = NULL;
			node->right = NULL;
			return (node);
		}
		*tokens = (*tokens)->next;
	}
	return (parse_redirection(&ptr));
}
t_ast_node	*parse_pipeline(t_token **tokens)
{
	t_token		*next;
	t_token		*ptr;
	t_ast_node	*pipe_node;
	
	ptr = *tokens;
	pipe_node = NULL;
	while (*tokens && (*tokens)->next)
	{
		next = (*tokens)->next;
		if (next->type == PipeSymbol)
		{
			(*tokens)->next = NULL;
			pipe_node = new_ast_node(next->type);
			pipe_node->left = parse_parenthese(&ptr);
			pipe_node->right = parse_pipeline(&(next->next));
			return (pipe_node);
		}
		*tokens = next;
	}
	return (parse_parenthese(&ptr));
}


t_ast_node	*parse_logical_operator(t_token **tokens)
{
	t_token		*next;
	t_token		*ptr;
	t_ast_node	*logical_node;
	
	ptr = *tokens;
	logical_node = NULL;
	while (*tokens && (*tokens)->next)
	{
		next = (*tokens)->next;
		if (next->type == LogicalAnd || next->type == LogicalOr)
		{
			(*tokens)->next = NULL;
			logical_node = new_ast_node(next->type);
			logical_node->left = parse_pipeline(&ptr);
			logical_node->right = parse_logical_operator(&(next->next));
			return (logical_node);
		}
		*tokens = next;
	}
	return (parse_pipeline(&ptr));
}

t_ast_node	*parse_tokens(t_token **tokens)
{
	if (!tokens && !*tokens)
		return (NULL);
	g_shell_data.nbr_cmd = 0;
	g_shell_data.simple_cmd->nbr_here_doc = 0;
	return (parse_logical_operator(tokens));
}
