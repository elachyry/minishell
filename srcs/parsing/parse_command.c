/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:31:45 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/06 17:11:19 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_nbr_of_args(t_token *ptr)
{
	int		count;

	count = 0;
	while (ptr && ptr->type == IDENTIFIER)
	{
		count++;
		ptr = ptr->next;
	}
	if (!count)
		count = 1;
	return (count);
}

static char	**create_args_table(t_token **ptr)
{
	char	**cmd;
	int		j;

	cmd = gc_malloc(sizeof(char *) * (get_nbr_of_args(*ptr) + 1));
	if (!cmd)
		return (NULL);
	j = 0;
	while (*ptr && (*ptr)->type == IDENTIFIER)
	{
		cmd[j] = (*ptr)->value;
		*ptr = (*ptr)->next;
		j++;
	}
	if (j == 0)
	{
		cmd[0] = ft_strdup("");
		j++;
	}
	cmd[j] = NULL;
	return (cmd);
}

t_ast_node	*parse_command_2(t_token **tokens, t_bool is_custom)
{
	char		**cmd;
	t_ast_node	*node;

	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	cmd = create_args_table(tokens);
	node = gc_malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->args = cmd;
	node->type = IDENTIFIER;
	node->left = NULL;
	if (!is_custom)
		node->right = parse_redirection(tokens);
	else
		node->right = NULL;
	return (node);
}

static char	**help_function(char *here_name, t_token **tokens)
{
	char	**cmd;

	if (!here_name)
	{
		cmd = gc_malloc(sizeof(char *) * 2);
		if (!cmd)
			return (NULL);
		cmd[0] = (*tokens)->value;
		*tokens = (*tokens)->next;
		cmd[1] = NULL;
	}
	else
	{
		cmd = gc_malloc(sizeof(char *) * 3);
		if (!cmd)
			return (NULL);
		cmd[0] = (*tokens)->value;
		cmd[1] = here_name;
		*tokens = (*tokens)->next;
		cmd[2] = NULL;
	}
	return (cmd);
}

//this function for parsing the command by Identifires 
//in double pointer and create a node type IDENTIFIER
t_ast_node	*parse_command(t_token	**tokens, char is_custom, char *here_name)
{
	char		**cmd;
	t_ast_node	*node;

	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	node = gc_malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = IDENTIFIER;
	node->left = NULL;
	cmd = NULL;
	cmd = help_function(here_name, tokens);
	node->args = cmd;
	if (!is_custom)
		node->right = parse_redirection(tokens);
	else
		node->right = NULL;
	return (node);
}
