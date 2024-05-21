/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:31:45 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/21 18:22:11 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_nbr_of_args(t_token *ptr)
{
	char	**tmp;
	int		count;

	count = 0;
	tmp = NULL;
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
	char	**tmp;
	char	**cmd;
	int		i;
	int		j;

	cmd = malloc(sizeof(char *) * (get_nbr_of_args(*ptr) + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	j = 0;
	tmp = NULL;
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

//this function for parsing the command by Identifires 
//in double pointer and create a node type IDENTIFIER
t_ast_node	*parse_command(t_token	**tokens, t_bool is_custom)
{
	char		**cmd;
	t_ast_node	*node;

	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	cmd = create_args_table(tokens);
	node = malloc(sizeof(t_ast_node));
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
