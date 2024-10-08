/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_sep_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:29:16 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/02 17:22:44 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_nbr_of_args(t_token *ptr, t_token *ptr2)
{
	int	count;
	int	count2;

	count = 0;
	count2 = 0;
	while (ptr && ptr->type == IDENTIFIER)
	{
		count++;
		ptr = ptr->next;
	}
	while (ptr2 && ptr2->type == IDENTIFIER)
	{
		count2++;
		ptr2 = ptr2->next;
	}
	return (count + count2);
}

t_ast_node	*parse_cmd_sep_args(t_token *tokens, t_token *args)
{
	int			i;
	char		**cmd;
	t_ast_node	*node;

	cmd = gc_malloc(sizeof(char *) * (get_nbr_of_args(tokens, args) + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	while (tokens && tokens->type == IDENTIFIER)
	{
		cmd[i++] = tokens->value;
		tokens = tokens->next;
	}
	while (args && args->type == IDENTIFIER)
	{
		cmd[i++] = args->value;
		args = args->next;
	}
	cmd[i] = NULL;
	node = new_ast_node(IDENTIFIER);
	if (node)
		node->args = cmd;
	return (node);
}
