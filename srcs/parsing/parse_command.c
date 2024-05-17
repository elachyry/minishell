/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:31:45 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/16 14:09:18 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	table_count(char **tab)
{
	int	i;

	if (!tab || !*tab)
		return (0);
	i = 0;
	while (*tab)
	{
		i++;
		tab++;
	}
	return (i);
}

static int	get_nbr_of_args(t_token *ptr)
{
	char	**tmp;
	int		count;

	count = 0;
	tmp = NULL;
	while (ptr && ptr->type == IDENTIFIER)
	{
		tmp = ft_split(ptr->value, ' ');
		count += table_count(tmp);
		ptr = ptr->next;
	}
	if (!count)
		count = 1;
	return (count);
}

static void	create_args_table(t_token **ptr, char **cmd)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = NULL;
	while (*ptr && (*ptr)->type == IDENTIFIER)
	{
		tmp = ft_split((*ptr)->value, ' ');
		i = -1;
		while (tmp && tmp[++i] != NULL)
		{
			cmd[j] = tmp[i];
			j++;
		}
		*ptr = (*ptr)->next;
	}
	if (j == 0)
	{
		cmd[0] = ft_strdup("");
		j++;
	}
	cmd[j] = NULL;
}

//this function for parsing the command by Identifires 
//in double pointer and create a node type IDENTIFIER
t_ast_node	*parse_command(t_token	**tokens, t_bool is_custom)
{
	char		**cmd;
	t_ast_node	*node;

	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	cmd = malloc(sizeof(char *) * (get_nbr_of_args(*tokens) + 1));
	if (!cmd)
		return (NULL);
	create_args_table(tokens, cmd);
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
