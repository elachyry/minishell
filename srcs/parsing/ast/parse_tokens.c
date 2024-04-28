/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:37:53 by melachyr          #+#    #+#             */
/*   Updated: 2024/04/28 22:24:00 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_ast_node	*parse_command(char **cmd)
{
	t_ast_node	*node;
	
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = IDENTIFIER;
	node->args = cmd;
	node->right = NULL;
	node->left = NULL;
	node->filename = NULL;
	return (node);
}

t_ast_node	*parse_pipeline(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;
	
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->right = right;
	node->left = left;
	node->type = PipeSymbol;
	node->args = NULL;
	node->filename = NULL;
	return (node);
}

t_ast_node	*parse_tokens(t_token *tokens)
{
	t_ast_node	*current;
	t_ast_node	*left;
	t_ast_node	*right;
	t_token		*token;
	
	current = NULL;
	left = NULL;
	right = NULL;
	token = tokens;
	while(token)
	{
		if (token->type == PipeSymbol)
		{
			left = current;
			current = NULL;
		}
		else if (token->type == LessThanOperator)
		{
			
		}
		else if (token->type == IDENTIFIER)
		{
			int	count = 0;
			t_token	*token_ptr = token;
			while (token_ptr->type != LessThanOperator
				&& token_ptr->type != GreaterThanOperator
				&& token_ptr->type != DoubleLessThanOperator
				&& token_ptr->type != PipeSymbol
				&& token_ptr->type != LogicalAnd
				&& token_ptr->type != LogicalOr && token_ptr->next)
			{
				count++;
				token_ptr = token_ptr->next;
			}
			// printf("test %s\n", token_ptr->value);
			char	**cmd = (char **)malloc(sizeof(char *) * (count + 1));
			if (!cmd)
				return (NULL);
			// printf("count = %d\n", count);
			int	i = -1;
			token_ptr = token;
			while (++i < count)
			{
				cmd[i] = token_ptr->value;
				token_ptr = token_ptr->next;
			}
			cmd[i] = NULL;
			// for(int i = 0; i < count; i++)
			// {
			// 	printf("%i ===> %s\n", i, cmd[i]);
			// }
			current = parse_command(cmd);
			token = token_ptr;
		}
		if (!left)
			left = current;
		else if(!right)
			right = current;
		else
		{
			left = parse_pipeline(right, left);
			right = current;
		}
		token = token->next;
	}
	printf("left %p | right %p | current %p\n", left, right, current);
	if (left && !right)
		return (left);
	else if (left && right)
        return parse_pipeline(right, left);
	else
		return (NULL);
}
