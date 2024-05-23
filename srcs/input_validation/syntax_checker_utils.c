/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:46:43 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/23 14:47:44 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_non_whitespace(char *result, char **tmp, int *l)
{
	if (!(*tmp[0] < 9 || *tmp[0] > 13))
	{
		if (!((*tmp[0] == ' ' || *tmp[0] == '\t') && *tmp[1] == '\0'))
			if (!(*tmp[0] == ' ' || *tmp[0] == '\t'))
				result = ft_strjoin_2(result, *tmp, 1);
		while ((*tmp[0] == ' ' || *tmp[0] == '\t') && **tmp != '\0')
		{
			(*tmp)++;
			*l = 1;
		}
	}
	return (result);
}

char	*epur_str(char *str)
{
	int		i;
	int		l;
	char	*tmp;
	char	*result;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	tmp = str + i;
	result = ft_strdup("");
	while (*tmp != '\0')
	{
		l = 0;
		result = handle_non_whitespace(result, &tmp, &l);
		if (l == 0)
			tmp++;
	}
	return (result);
}

t_bool	has_invalid_single_ampersand(const char *input)
{
	int			s_q_count;
	int			d_q_count;
	const char	*temp;

	s_q_count = 0;
	d_q_count = 0;
	while (*input)
	{
		update_quote_counts(*input, &s_q_count, &d_q_count);
		if (!(s_q_count % 2) && !(d_q_count % 2) && *input == '&')
		{
			temp = input + 1;
			while (*temp == ' ' || *temp == '\t')
				temp++;
			if (*temp != '&' && *temp != '\0' && *(input - 1) != '&')
				return (false);
		}
		input++;
	}
	return (true);
}

t_bool	has_misplaced_operators_2(const char *input)
{
	int			next_command;
	int			s_q;
	int			d_q;
	t_bool		enc_and_or;
	const char	*temp;

	init_var(&next_command, &s_q, &d_q, &enc_and_or);
	if (*input == '|' || *input == '&')
		return (false);
	while (*input)
	{
		update_quote_counts(*input, &s_q, &d_q);
		if (!(s_q % 2) && !(d_q % 2) && (*input == '|' || *input == '&'))
		{
			if (operator_mispla(&input, &next_command, &enc_and_or, &temp))
				return (false);
		}
		else if (!ft_isspace(*input))
		{
			next_command = 0;
			enc_and_or = false;
		}
		input++;
	}
	return (!next_command);
}

t_bool	has_invalid_redirections_2(const char *input)
{
	int		s_q;
	int		d_q;
	t_bool	enc_and_or;

	s_q = 0;
	d_q = 0;
	enc_and_or = false;
	while (*input)
	{
		update_quote_counts(*input, &s_q, &d_q);
		if (!check_redirection_operator(&input, &s_q, &d_q, &enc_and_or))
			return (false);
		input++;
	}
	return (true);
}
