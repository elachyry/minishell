/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:50:21 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/29 11:39:04 by melachyr         ###   ########.fr       */
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

static void	help_function(t_ast_node **node, t_token *token, char *here_name)
{
	if (!here_name)
	{
		(*node)->args = malloc(sizeof(char *) * 2);
		if (!(*node)->args)
			return ;
		(*node)->args[0] = token->value;
		(*node)->args[1] = NULL;
	}
	else
	{
		(*node)->args = malloc(sizeof(char *) * 3);
		if (!(*node)->args)
			return ;
		(*node)->args[0] = token->value;
		(*node)->args[1] = here_name;
		(*node)->args[2] = NULL;
	}
}

t_ast_node	*new_ast_file_node(t_token *token, char *here_name)
{
	t_ast_node	*node;

	if (token == NULL)
		return (NULL);
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = token->type;
	help_function(&node, token, here_name);
	node->left = NULL;
	node->right = NULL;
	return (node);
}
