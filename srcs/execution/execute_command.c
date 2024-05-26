/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:42:54 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/26 18:32:48 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	manage_builtins(char **args)
{
	int	old_stdin;
	int	old_stdout;
	int	status;

	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	status = 0;
	if (redirect_files_buildin())
	{
		dup2(old_stdin, STDIN_FILENO);
		dup2(old_stdout, STDOUT_FILENO);
		return (1);
	}
	status = execute_builtin(args);
	dup2(old_stdin, STDIN_FILENO);
	dup2(old_stdout, STDOUT_FILENO);
	return (status);
}

static void	wait_for_cmd(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
	{
		if (WEXITSTATUS(*status) != 0)
			g_shell_data.simple_cmd->files = NULL;
	}
	g_shell_data.simple_cmd->is_parenthis++;
	g_shell_data.simple_cmd->is_parenthis_red_ch = false;
}

static void	process_cmd(char **args)
{
	int	status;

	status = get_cmd_path(args[0]);
	if (status == 4)
		return ;
	cmd_not_found(args, status);
	execve(g_shell_data.simple_cmd->cmd_path,
		args, g_shell_data.environment);
	execve_fail(args);
}


void expand_env_variables_2(char **args)
{
    int i;
    int in_single_quotes;
    int in_double_quotes;
    char *tmp;

    if (!args)
        return;

    for (i = 0; args[i]; ++i)
    {
        in_single_quotes = 0;
        in_double_quotes = 0;
        tmp = args[i];
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
                args[i] = shearch_and_replace(args[i]);
                break;
            }
            tmp++;
        }
    }
}

size_t count_non_empty_args(char **args)
{
    size_t count = 0;
    for (size_t i = 0; args[i] != NULL; i++)
    {
        if (args[i][0] != '\0')
        {
            count++;
        }
    }
    return count;
}

char **remove_empty_args(char **args)
{
    size_t num_non_empty = count_non_empty_args(args);

    char **new_args = malloc((num_non_empty + 1) * sizeof(char *));
    if (!new_args)
    {
        return NULL; // Handle memory allocation failure
    }

    size_t j = 0;
    for (size_t i = 0; args[i] != NULL; i++)
    {
        if (args[i][0] != '\0')
        {
            new_args[j++] = args[i];
        }
        else
        {
            free(args[i]);
        }
    }
    new_args[j] = NULL;

    // We do not free the original args array here to avoid freeing the pointers we are still using.
    return new_args;
}
static int handle_d_q_2(char current_char, int in_single_quotes, int in_double_quotes) {
    if (current_char == '\"' && !in_single_quotes) {
        in_double_quotes = !in_double_quotes;
    }
    return in_double_quotes;
}

static int handle_s_q_2(char current_char, int in_double_quotes, int in_single_quotes) {
    if (current_char == '\'' && !in_double_quotes) {
        in_single_quotes = !in_single_quotes;
    }
    return in_single_quotes;
}

static char *allocate_new_str_2(int length) {
    char *new_str = malloc(length + 1);
    if (!new_str) {
        return NULL;
    }
    return new_str;
}

static char *remove_all_quotes_2(char *str) {
    char *new_str;
    int i, j, in_s_q, in_d_q;

    in_s_q = 0;
    in_d_q = 0;
    new_str = allocate_new_str_2(strlen(str));
    if (!new_str) {
        return NULL;
    }
    i = -1;
    j = 0;
    while (str[++i]) {
        in_d_q = handle_d_q_2(str[i], in_s_q, in_d_q);
        in_s_q = handle_s_q_2(str[i], in_d_q, in_s_q);
        if (!(str[i] == '\"' && !in_s_q) && !(str[i] == '\'' && !in_d_q)) {
            new_str[j] = str[i];
            j++;
        }
    }
    new_str[j] = '\0';
    return new_str;
}

static void expand_quotes_2(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        char *new_str = remove_all_quotes_2(args[i]);
        free(args[i]);
        args[i] = new_str;
    }
}
void process_file_list(char **file_list, char ***args, int *n_args)
{
    char **filenames;
    int i;

    filenames = ft_split(*file_list, ' ');
    free(*file_list);
    *file_list = NULL;
    if (filenames)
    {
        *args = realloc(*args, (*n_args + 2) * sizeof(char *));
        if (*args == NULL)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        (*args)[*n_args] = ft_strdup(filenames[0]);
        i = 1;
        while (filenames[i])
        {
            // Reallocate the args array to make room for the new argument
            *args = realloc(*args, (*n_args + i + 2) * sizeof(char *));
            if (*args == NULL)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            // Insert the new argument
            (*args)[*n_args + i] = ft_strdup(filenames[i]);
            i++;
        }
        // Update the number of arguments
        *n_args += i;
        // Null-terminate the args array
        (*args)[*n_args] = NULL;
        free(filenames);
    }
}
void	update_file_list(char **file_list, const char *entry_name)
{
	char	*filename_with_space;
	char	*new_file_list;

	filename_with_space = ft_strjoin(entry_name, " ");
	if (*file_list)
		new_file_list = ft_strjoin(*file_list, filename_with_space);
	else
		new_file_list = ft_strdup(filename_with_space);
	free(filename_with_space);
	if (*file_list)
		free(*file_list);
	*file_list = new_file_list;
}

int process_pattern(const char **string, const char **pattern, \
const char **str_backup, const char **pattern_backup)
{
    if (**pattern == '*')
    {
        *pattern_backup = ++(*pattern);
        *str_backup = *string;
    }
    else if (**pattern == **string)
    {
        (*pattern)++;
        (*string)++;
    }
    else if (*pattern_backup)
    {
        *pattern = *pattern_backup;
        *string = ++(*str_backup);
    }
    else
        return (0);
    return (1);
}

int match(const char *string, const char *pattern)
{
    const char *str_backup;
    const char *pattern_backup;

    str_backup = NULL;
    pattern_backup = NULL;
    while (*string)
    {
        if (!process_pattern(&string, &pattern, &str_backup, &pattern_backup))
            return (0);
    }
    while (*pattern == '*')
        pattern++;
    return (!*pattern);
}

int check_wildcard(char *arg)
{
    int has_wildcard;
    char *tmp;

    has_wildcard = 0;
    tmp = arg;
    while (*tmp)
    {
        if (*tmp == '*')
        {
            has_wildcard = 1;
            break;
        }
        tmp++;
    }
    return (has_wildcard);
}

char *remove_quotes_and_advance(char *arg)
{
    char *tmp;

    tmp = remove_all_quotes_2(arg);
    free(arg);
    return tmp;
}

void process_wildcard(char *arg, char **file_list)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.' && arg[0] != '.')
            continue;
        if (match(entry->d_name, arg))
            update_file_list(file_list, entry->d_name);
    }
    closedir(dir);
}
void expand_wildcards(char ***args)
{
    int i = 0;
    char *file_list = NULL;
    int n_args = 0;
    int in_quotes = 0;

    // Calculate the number of arguments
    while ((*args)[n_args])
        n_args++;

    while (i < n_args)
    {
        // Check if the argument starts with a quote
        if ((*args)[i][0] == '"' || (*args)[i][0] == '\'')
            in_quotes = 1;
        else
            in_quotes = 0;

        // Only expand wildcards if not in quotes
        if (!in_quotes && check_wildcard((*args)[i]))
        {
            process_wildcard((*args)[i], &file_list);
            if (file_list)
            {
                process_file_list(&file_list, args, &i);
                // Recalculate the number of arguments after processing the file list
                n_args = 0;
                while ((*args)[n_args])
                    n_args++;
            }
        }
        i++;
    }
}

int	execute_command(char **args)
{
	int		status;
	pid_t	pid;
	char    **new_args;

	expand_env_variables_2(args);
	new_args = remove_empty_args(args);
	// // int i = 0;
	// // while (new_args[i])
	// // {
	// // 	printf("args[%d] = %d\n", i, new_args[i][0]);
	// // 	i++;
	// // }
	expand_wildcards(&new_args);
	expand_quotes_2(new_args);
	status = 0;
	signal(SIGQUIT, sigquit_handler);
	if (check_if_builtin(new_args[0]))
		return (manage_builtins(new_args));
	else
	{
		pid = fork();
		if (pid == -1)
			perror_message("fork", EXIT_FAILURE);
		else if (pid == 0)
		{
			if (g_shell_data.simple_cmd->is_parenthis > 1
				|| !g_shell_data.simple_cmd->is_parenthis
				|| (g_shell_data.simple_cmd->is_parenthis == 1
					&& g_shell_data.simple_cmd->is_parenthis_red_ch == 1))
				redirect_files();
			process_cmd(new_args);
		}
		else
			wait_for_cmd(pid, &status);
		return (WEXITSTATUS(status));
	}
}
