/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:37:53 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/04 17:35:29 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_ast_node	*parse_command(char **cmd)
// {
// 	t_ast_node	*node;
	
// 	node = malloc(sizeof(t_ast_node));
// 	if (!node)
// 		return (NULL);
// 	node->type = IDENTIFIER;
// 	node->args = cmd;
// 	node->right = NULL;
// 	node->left = NULL;
// 	node->filename = NULL;
// 	return (node);
// }

// t_ast_node	*parse_pipeline(t_ast_node *right, t_ast_node *left)
// {
// 	t_ast_node	*node;
	
// 	node = malloc(sizeof(t_ast_node));
// 	if (!node)
// 		return (NULL);
// 	node->right = right;
// 	node->left = left;
// 	node->type = PipeSymbol;
// 	node->args = NULL;
// 	node->filename = NULL;
// 	return (node);
// }

// t_ast_node	*parse_redirection(t_ast_node *left, char *filename)
// {
// 	t_ast_node	*node;

// 	node = malloc(sizeof(t_ast_node));
// 	if (!node)
// 		return (NULL);
// 	node->type = LessThanOperator;
// 	node->left = left;
// 	node->right = NULL;
// 	node->args = NULL;
// 	node->filename = filename;
// 	return (node);
// }

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
	printf("token->value %p\n", token);
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
	// for(int i = 0; i < count; i++)
	// {
	// 	dprintf(2, "%i ===> %s\n", i, cmd[i]);
	// }
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
		// printf("hi  parse_redirection\n");
		// dprintf(2, "ptr %s\n", ptr->value);
		// dprintf(2, "tokens %s\n", (*tokens)->value);
		redirection_node = new_ast_node((*tokens)->type);
		printf("ptr->value %s\n", ptr->value);
		*tokens = NULL;
		printf("ptr->value %s\n", ptr->value);
		redirection_node->left = parse_redirection(tokens);
		redirection_node->right = new_ast_file_node(ptr->next);
		return (redirection_node);
	}
	while (*tokens && (*tokens)->next)
	{
		// dprintf(2, "parse_redirection\n");
		next = (*tokens)->next;
		if (next->type == LessThanOperator || next->type == DoubleLessThanOperator
			|| next->type == GreaterThanOperator || next->type == DoubleGreaterThanOperator)
		{
			redirection_node = new_ast_node(next->type); 
			(*tokens)->next = NULL;
			// dprintf(2, "tokens red  %p\n", (*tokens)->next);
			// dprintf(2, "after %s\n", (*tokens)->next->value);
			redirection_node->right = new_ast_file_node(next->next);
			// dprintf(2, "ptr %s\n", ptr->value);
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
			// dprintf(2, "tokens = NULL%s\n", (*tokens)->next->value);
			(*tokens)->next = NULL;
			// dprintf(2, "ptr %p\n", ptr->next->next);
			pipe_node = new_ast_node(next->type);
			pipe_node->left = parse_redirection(&ptr);
			pipe_node->right = parse_pipeline(&(next->next));
			return (pipe_node);
		}
		*tokens = next;
	}
	return (parse_redirection(&ptr));
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
			printf("tokens->value %s\n", next->value);
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
	return (parse_logical_operator(tokens));
}

// t_ast_node	*parse_tokens(t_token *tokens)
// {
// 	t_ast_node	*current;
// 	t_ast_node	*left;
// 	t_ast_node	*right;
// 	t_token		*token;
	
// 	current = NULL;
// 	left = NULL;
// 	right = NULL;
// 	token = tokens;
// 	while(token)
// 	{
// 		if (token->type == PipeSymbol)
// 		{
// 			left = current;
// 			current = NULL;
// 		}
// 		else if (token->type == LessThanOperator)
//         {
//             if (token->next)
//             {
//                 current = parse_redirection(current, token->next->value);
//                 token = token->next;
//             }
//         }
// 		else if (token->type == IDENTIFIER)
// 		{
// 			int	count = 0;
// 			t_token	*token_ptr = token;
// 			while (token_ptr->type != LessThanOperator
// 				&& token_ptr->type != GreaterThanOperator
// 				&& token_ptr->type != DoubleLessThanOperator
// 				&& token_ptr->type != PipeSymbol
// 				&& token_ptr->type != LogicalAnd
// 				&& token_ptr->type != LogicalOr && token_ptr->next)
// 			{
// 				count++;
// 				token_ptr = token_ptr->next;
// 			}
// 			// printf("test %s\n", token_ptr->value);
// 			char	**cmd = (char **)malloc(sizeof(char *) * (count + 1));
// 			if (!cmd)
// 				return (NULL);
// 			// printf("count = %d\n", count);
// 			int	i = -1;
// 			token_ptr = token;
// 			while (++i < count)
// 			{
// 				cmd[i] = token_ptr->value;
// 				token_ptr = token_ptr->next;
// 			}
// 			cmd[i] = NULL;
// 			// for(int i = 0; i < count; i++)
// 			// {
// 			// 	printf("%i ===> %s\n", i, cmd[i]);
// 			// }
// 			current = parse_command(cmd);
// 			token = token_ptr;
// 		}
// 		if (!left)
// 			left = current;
// 		else if(!right)
// 			right = current;
// 		else
// 		{
// 			left = parse_pipeline(right, left);
// 			right = current;
// 		}
// 		token = token->next;
// 	}
// 	printf("left %p | right %p | current %p\n", left, right, current);
// 	if (left && !right)
// 		return (left);
// 	else if (left && right)
//         return parse_pipeline(right, left);
// 	else
// 		return (NULL);
// }
