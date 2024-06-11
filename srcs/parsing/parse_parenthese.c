/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthese.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:15:09 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/11 23:28:23 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_nbr_of_cmd(t_token *ptr)
{
	int	count;

	count = 0;
	while (ptr && ptr->type == OpeningParenthesis)
		ptr = ptr->next;
	count = 0;
	while (ptr && ptr->type != ClosingParenthesis)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

t_ast_node	*extract_bash_cmd(t_token **tokens)
{
	int			i;
	int			count;
	char		**cmd;
	t_token		*ptr;
	t_ast_node	*node;

	count = get_nbr_of_cmd((*tokens)->next);
	cmd = gc_malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return (NULL);
	ptr = (*tokens)->next;
	while (ptr && ptr->type == OpeningParenthesis)
		ptr = ptr->next;
	i = -1;
	while (++i < count)
	{
		cmd[i] = ptr->value;
		ptr = ptr->next;
	}
	cmd[i] = NULL;
	*tokens = ptr;
	node = new_ast_node(OpeningParenthesis);
	if (node)
		node->args = cmd;
	g_shell_data.parenth_count++;
	return (node);
}

//this function for parsing parenthese by grouping all
//tokens till first closing parenthese in double pointer
//and create a node type parenthese
t_ast_node	*parse_parenthese(t_token **tokens)
{
	t_token		*next;
	t_token		*ptr;

	ptr = *tokens;
	while (*tokens)
	{
		next = *tokens;
		if (next->type == OpeningParenthesis)
		{
			g_shell_data.simple_cmd->is_parenthis = 1;
			return (extract_bash_cmd(tokens));
		}
		*tokens = (*tokens)->next;
	}
	return (parse_command_2(&ptr, false));
}
