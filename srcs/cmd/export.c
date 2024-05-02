/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 05:54:34 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/02 06:09:24 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void printEnvironmentList()
{
    t_env *current = g_shell_data.environment_list;
    while (current != NULL)
    {
        printf("declare -x %s=\"%s\"\n", current->key, current->value);
        current = current->next;
    }
}

// Function to check if a string is a valid environment variable identifier
t_bool isValidIdentifier(char *str)
{
    if (!isalpha(str[0]) && str[0] != '_')
    {
        return false;
    }
    for (size_t i = 1; str[i] != '\0'; i++)
    {
        if (!isalnum(str[i]) && str[i] != '_')
        {
            return false;
        }
    }
    return true;
}

int exportErrorMessage(char *identifier)
{
    fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", identifier);
    return (1);
}

// Function to export environment variables
int ft_export(char **argv)
{
    // If called with no arguments, print all environment variables
    if (argv[1] == NULL)
    {
        printEnvironmentList();
        return 0;
    }

    int i = 1;
    // Loop through each argument and export the variables
    while (argv[i] != NULL)
    {
        char *arg = argv[i];

        // Extract key and value from the argument
        char *key = extract_key(arg);
        char *value = extract_value(arg);

        // Check if the key is a valid identifier
        if (!isValidIdentifier(key))
        {
            free(key);
            free(value);
            return (exportErrorMessage(arg));
        }

        // Update environment variable and the environment list
        add_to_environment_list(create_environment_node(key, value));
        free(key);
        free(value);
        i++;
    }

    return 0;
}