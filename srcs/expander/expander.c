/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:42:28 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/15 21:49:42 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char *remove_all_quotes(char *str)
// {
//     char *new_str;
//     int i, j;
//     int in_single_quotes = 0;
//     int in_double_quotes = 0;

//     new_str = malloc(strlen(str) + 1); // Allocate memory for new string
//     if (!new_str)
//         return NULL;

//     i = 0;
//     j = 0;
//     while (str[i])
//     {
//         if (str[i] == '\"' && !in_single_quotes) // If the character is a double quote and we're not inside single quotes
//         {
//             in_double_quotes = !in_double_quotes; // Toggle the in_double_quotes flag
//         }
//         else if (str[i] == '\'' && !in_double_quotes) // If the character is a single quote and we're not inside double quotes
//         {
//             in_single_quotes = !in_single_quotes; // Toggle the in_single_quotes flag
//         }
//         else
//         {
//             new_str[j] = str[i]; // Copy it to the new string
//             j++;
//         }
//         i++;
//     }
//     new_str[j] = '\0'; // Null-terminate the new string

//     return (new_str);
// }



// echo '\" ' " \"\""
// echo \\\" \\\" \\\" \\\"\\\"\\\" \\\'\\\'\\\'

// echo " $USER  \$ "'$PWD'

char *remove_all_quotes(t_token *token, char *str)
{
	char *new_str;
	int i, j;
	int in_single_quotes = 0;
	int in_double_quotes = 0;
	int in_variable = 0;

	new_str = malloc(ft_strlen(str) + 1); // Allocate memory for new string
	if (!new_str)
		return NULL;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"' && !in_single_quotes) // If the character is a double quote and we're not inside single quotes
		{
			if (token->prev && token->prev->type == DoubleLessThanOperator)
				g_shell_data.simple_cmd->should_expand = false;
			in_double_quotes = !in_double_quotes; // Toggle the in_double_quotes flag
			if (str[i+1] == '$') // If the next character is a $, we're inside a variable
			{
				in_variable = 1;
			}
			else if (in_variable) // If we're at the end of a variable, stop marking it
			{
				in_variable = 0;
			}
		}
		else if (str[i] == '\'' && !in_double_quotes) // If the character is a single quote and we're not inside double quotes
		{
			if (token->prev && token->prev->type == DoubleLessThanOperator)
				g_shell_data.simple_cmd->should_expand = false;
			in_single_quotes = !in_single_quotes; // Toggle the in_single_quotes flag
		}
		else
		{
			new_str[j] = str[i]; // Copy it to the new string
			j++;
		}
		i++;
	}
	new_str[j] = '\0'; // Null-terminate the new string

	return (new_str);
}

t_token	*expand_quotes(t_token *tokens)
{
	t_token	*token;
	char	*tmp;

	token = tokens;
	while (token)
	{
		if (token->type == IDENTIFIER)
		{
			tmp = remove_all_quotes(token, token->value);
			free(token->value);
			token->value = tmp;
		}
		token = token->next;
	}
	return (tokens);
}
char	*ft_getenv(char *name, t_env *env)
{
	t_env	*var;
	int		max;

	var = env;
	while (var)
	{
		max = ft_strlen(var->key);
		if ((int) ft_strlen(name) > max)
			max = ft_strlen(name);
		if (!ft_strncmp(var->key, name, max) && var->value)
			return (var->value);
		var = var->next;
	}
	return ("");
}

char	*append_char(char *str, char c)
{
	char	*tmp;
	int		len;

	if (!str)
	{
		tmp = malloc(2);
		tmp[0] = c;
		tmp[1] = 0;
		return (tmp);
	}
	len = ft_strlen(str);
	tmp = malloc(len + 2);
	ft_strlcpy(tmp, str, len + 1);
	tmp[len] = c;
	tmp[len + 1] = 0;
	return (tmp);
}
char	*get_var_value(char **value, char *line, t_env *env)
{
	char	*name;

	name = NULL;
	if (*line == '?')
	{
		*value = ft_itoa(g_shell_data.status);
		return (line);
	}
	if (!ft_isalnum(*line) && *line != '_')
	{
		*value = "$";
		if (*line != -1)
			return (line - 1);
		return (line);
	}
	while (*line == '_' || ft_isalnum(*line))
	{
		name = append_char(name, *line);
		line++;
	}
	if (!name)
		name = "";
	*value = ft_getenv(name, env);
	return (line - 1);
}

// char	*shearch_and_replace(char *line)
// {
//     char	*ret;
//     char	*value;
//     int in_single_quotes = 0;
//     int in_double_quotes = 0;

//     ret = "";
//     while (*line)
//     {
//         if (*line == '\'')
//         {
//             in_single_quotes = !in_single_quotes;
//         }
//         else if (*line == '\"')
//         {
//             in_double_quotes = !in_double_quotes;
//         }
//         else if (*line == '$' && (!in_single_quotes || in_double_quotes))
//         {
//             line = get_var_value(&value, line + 1, g_shell_data.environment_list);
//             ret = ft_strjoin(ret, value);
//         }
//         else
//         {
//             ret = append_char(ret, *line);
//         }
//         line++;
//     }
//     return (ret);
// }

char	*shearch_and_replace(char *line)
{
	char	*ret;
	char	*value;
	int in_single_quotes = 0;
	int in_double_quotes = 0;
	int nested_quotes = 0;

	ret = "";
	while (*line)
	{
		if (*line == '\'')
		{
			if (!in_double_quotes)
			{
				in_single_quotes = !in_single_quotes;
			}
			else
			{
				nested_quotes = !nested_quotes;
			}
			ret = append_char(ret, *line);
		}
		else if (*line == '\"')
		{
			if (!in_single_quotes)
			{
				in_double_quotes = !in_double_quotes;
			}
			else
			{
				nested_quotes = !nested_quotes;
			}
			ret = append_char(ret, *line);
		}
		else if (*line == '$' && (!in_single_quotes || (in_double_quotes && !nested_quotes)))
		{
			line = get_var_value(&value, line + 1, g_shell_data.environment_list);
			ret = ft_strjoin(ret, value);
		}
		else
		{
			ret = append_char(ret, *line);
		}
		line++;
	}
	return (ret);
}

t_token	*expand_env_variable(t_token *tokens)
{
	t_token	*tok;
	int in_single_quotes;
	int in_double_quotes;
	char *tmp;

	tok = tokens;
	while (tok)
	{
		if (tok->prev && tok->prev->type == DoubleLessThanOperator)
		{
			tok = tok->next;
			continue;
		}
		in_single_quotes = 0;
		in_double_quotes = 0;
		tmp = tok->value;
		while (*tmp)
		{
			if (*tmp == '\'')
			{
				in_single_quotes = !in_single_quotes;
			}
			else if (*tmp == '\"')
			{
				in_double_quotes = !in_double_quotes;
			}
			else if (*tmp == '$' && (!in_single_quotes || in_double_quotes))
			{
				tok->value = shearch_and_replace(tok->value);
				break;
			}
			tmp++;
		}
		tok = tok->next;
	}
	return (tokens);
}

int match(const char *string, const char *pattern)
{
    while (*string)
    {
        if (*pattern == '*')
        {
            if (match(string, pattern + 1))
                return 1;
            string++;
        }
        else if (*pattern == *string)
        {
            pattern++;
            string++;
        }
        else
        {
            return 0;
        }
    }

    while (*pattern == '*')
        pattern++;

    return !*pattern;
}

// t_token *expand_wildcards(t_token *tokens)
// {
//     t_token *tok;
//     char *tmp;
//     DIR *dir;
//     struct dirent *entry;

//     tok = tokens;
//     while (tok)
//     {
//         tmp = tok->value;
//         while (*tmp)
//         {
//             if (*tmp == '*')
//             {
//                 dir = opendir(".");
//                 if (dir == NULL)
//                 {
//                     perror("opendir");
//                     return (tokens);
//                 }
//                 while ((entry = readdir(dir)) != NULL)
//                 {
//                     // Skip hidden files unless the pattern starts with a dot
//                     if (entry->d_name[0] == '.' && tok->value[0] != '.')
//                         continue;

//                     if (match(entry->d_name, tok->value))
//                     {
//                         printf("%s\n", entry->d_name);
//                     }
//                 }
//                 closedir(dir);
//                 break;
//             }
//             tmp++;
//         }
//         tok = tok->next;
//     }
//     return (tokens);
// }

t_token *expand_wildcards(t_token *tokens)
{
    t_token *tok;
    char *tmp;
    DIR *dir;
    struct dirent *entry;
    char *file_list = NULL;

    tok = tokens;
    while (tok)
    {
        tmp = tok->value;
        while (*tmp)
        {
            if (*tmp == '*')
            {
                dir = opendir(".");
                if (dir == NULL)
                {
                    perror("opendir");
                    return (tokens);
                }
                while ((entry = readdir(dir)) != NULL)
                {
                    // Skip hidden files unless the pattern starts with a dot
                    if (entry->d_name[0] == '.' && tok->value[0] != '.')
                        continue;

                   	if (match(entry->d_name, tok->value))
					{
					    // Concatenate the matching filename to the file list
					    char *filename_with_space = ft_strjoin(entry->d_name, " ");
					    char *new_file_list;
					    if (file_list)
					    {
					        new_file_list = ft_strjoin(file_list, filename_with_space);
					    }
					    else
					    {
					        new_file_list = ft_strjoin("", filename_with_space);
					    }
					    free(filename_with_space);
					    if (file_list)
					        free(file_list);
					    file_list = new_file_list;
					}
                }
                closedir(dir);
                break;
            }
            tmp++;
        }
        if (file_list)
        {
            if (tok)
            {
                tok->value = file_list;
            }
            else
            {
                // Handle the case where tok is null
                // You might want to return an error or create a new token
            }
        }
        tok = tok->next;
    }

    return (tokens);
}

t_token *expand_tokens(t_token *tokens)
{
	tokens = expand_env_variable(tokens);
	tokens = expand_quotes(tokens);
    tokens = expand_wildcards(tokens);
	return (tokens);
}

// t_token	*expand_env_variable(t_token *tokens)
// {
// 	t_token	*tok;

// 	tok = tokens;
// 	while (tok)
// 	{
// 		if (tok->value)
// 			tok->value = shearch_and_replace(tok->value);
// 		tok = tok->next;
// 	}
// 	return (tokens);
// }
