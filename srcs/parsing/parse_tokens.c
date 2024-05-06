/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:37:53 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/06 10:48:31 by melachyr         ###   ########.fr       */
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

t_ast_node	*link_redirections(t_token **tokens, t_token *ptr)
{
	t_ast_node	*node;
	
	node = new_ast_node((*tokens)->type);
	*tokens = NULL;
	node->left = parse_redirection(tokens);
	node->right = new_ast_file_node(ptr->next);
	return (node);
}

t_ast_node	*parse_command(t_token	**tokens)
{
	int			count;
	int			i;
	char		**cmd;
	t_token		*ptr;
	t_ast_node	*node;

	ptr = *tokens;
	count = 0;
	while (ptr && ptr->type == IDENTIFIER)
	{
		count++;
		ptr = ptr->next;
	}	
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
	node->right = NULL;
	return (node);
}

t_ast_node	*parse_redirection(t_token **tokens)
{
	t_ast_node	*redirection_node;
	t_token		*ptr;
	t_token		*next;

	if (!*tokens)
		return (NULL);
	ptr = *tokens;
	if ((*tokens)->type == LessThanOperator || (*tokens)->type == DoubleLessThanOperator
		|| (*tokens)->type == GreaterThanOperator || (*tokens)->type == DoubleGreaterThanOperator)
	{

		redirection_node = new_ast_node((*tokens)->type);
		*tokens = NULL;
		redirection_node->left = parse_redirection(tokens);
		redirection_node->right = new_ast_file_node(ptr->next);
		return (redirection_node);
	}
	while (*tokens && (*tokens)->next)
	{
		next = (*tokens)->next;
		if (next->type == LessThanOperator || next->type == DoubleLessThanOperator
			|| next->type == GreaterThanOperator || next->type == DoubleGreaterThanOperator)
		{
			redirection_node = new_ast_node(next->type); 
			(*tokens)->next = NULL;
			redirection_node->right = new_ast_file_node(next->next);
			redirection_node->left = parse_redirection(&ptr);
			return (redirection_node);
		}
		*tokens = next;
	}
	return (parse_command(&ptr));
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
			pipe_node->left = parse_redirection(&ptr);
			pipe_node->right = parse_pipeline(&(next->next));
			return (pipe_node);
		}
		*tokens = next;
	}
	return (parse_redirection(&ptr));
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
	return (parse_pipeline(&ptr));
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
			logical_node->left = parse_parenthese(&ptr);
			logical_node->right = parse_logical_operator(&(next->next));
			return (logical_node);
		}
		*tokens = next;
	}
	return (parse_parenthese(&ptr));
}

t_ast_node	*parse_tokens(t_token **tokens)
{
	if (!tokens && !*tokens)
		return (NULL);
	return (parse_logical_operator(tokens));
}
