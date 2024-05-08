/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:29:34 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/08 13:55:36 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_cmd_path(char	*args)
{
	char			*cmd;
	char			*path;
	
	cmd = ft_strrchr(args, '/');
	// printf("cmd %s\n", g_shell_data.ast->args[0]);
	if (cmd)
	{
		if (access(cmd, X_OK) != -1)
		{
			g_shell_data.simple_cmd->cmd_path = args;
			// printf("simple_cmd path %s\n", g_shell_data.simple_cmd->cmd_path);
			return (1);
		}
	}
	else
	{
		cmd = args;
		// printf("cmd %s\n", cmd);
		while (*g_shell_data.path)
		{
			// printf("path %s\n", *g_shell_data.path);
			path = ft_strjoin(*g_shell_data.path, "/");
			path = ft_strjoin(path, cmd);
			// printf("path %s\n", path);
			if (access(path, X_OK) != -1)
			{
				// printf("before \n");
				g_shell_data.simple_cmd->cmd_path = path;
				// printf("simple_cmd path %s\n", g_shell_data.simple_cmd->cmd_path);
				return (1);
			}
			free(path);
			g_shell_data.path++;
		}
	}
	
	return (0);
}

// void	execute_single_cmd(void)
// {
// 	int	status;

// 	int	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (!get_cmd_path())
// 		{
// 			ft_putstr_fd("command not found: ", 2);
// 			ft_putstr_fd(g_shell_data.ast->args[0], 2);
// 			ft_putstr_fd("\n", 2);
// 			exit(127);
// 		}
// 		execve(g_shell_data.simple_cmd->cmd_path, g_shell_data.ast->args, NULL);
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		if (WIFEXITED(status))
// 			g_shell_data.status = WEXITSTATUS(status);
// 	}
// }


// void	execute_pipeline(t_ast_node	**ast)
// {
// 	t_ast_node	*ptr;

// 	ptr = *ast;
// 	while (*ast)
// 	{
// 		if ((*ast)->type == PipeSymbol)
// 		{
// 			execute
// 		}
// 	}
// }


int execute_command(char **args)
{
    pid_t pid = fork();
    int status = 0;
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (!get_cmd_path(args[0]))
        {
            ft_putstr_fd("command not found: ", 2);
            ft_putstr_fd(args[0], 2);
            ft_putstr_fd("\n", 2);
            exit(127);
        }
        execve(g_shell_data.simple_cmd->cmd_path, args, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            // dprintf(2, "status in wait %d\n", WEXITSTATUS(status));
            g_shell_data.status = 199;//WEXITSTATUS(status);
        }
    }
    return status;
}


void execute_ast(t_ast_node *node) 
{
	if (node == NULL) {
		return;
	}
	// int status = 0; 
		//dprintf(2, "node->arg %s | node->value %s\n", node->args != NULL ? node->args[0]: "NULL" , get_token_type_name(node->type));

	if (node->type == IDENTIFIER) {
		g_shell_data.status = execute_command(node->args);
		// printf("status in IDENTIFIER %d\n", status);
	} else if (node->type == PipeSymbol) {
		//dprintf(2, "PipeSymbol\n");
		int pipefd[2];
		if (pipe(pipefd) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid_t left_pid = fork();
		if (left_pid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		} else if (left_pid == 0) {
			close(pipefd[0]); 
			dup2(pipefd[1], STDOUT_FILENO); 
			close(pipefd[1]); 
			//dprintf(2, "left node pipe %s\n", get_token_type_name(node->left->type));
			// dprintf(2, "left %s\n", node->left->args[0]);
			execute_ast(node->left); 
			exit(EXIT_SUCCESS);
		}
		
		pid_t right_pid = fork();
		if (right_pid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		} else if (right_pid == 0) {
			close(pipefd[1]); 
			dup2(pipefd[0], STDIN_FILENO); 
			close(pipefd[0]); 
			//dprintf(2, "right node pipe %s\n", get_token_type_name(node->right->type));
			execute_ast(node->right); 
			// dprintf(2, "status in right %d\n", WEXITSTATUS(g_shell_data.status));
			exit(WEXITSTATUS(g_shell_data.status));
		}

		close(pipefd[0]); 
		close(pipefd[1]); 
		int left_status, right_status;
		waitpid(left_pid, &left_status, 0);
		waitpid(right_pid, &right_status, 0);

		if (WIFEXITED(right_status)) {
			g_shell_data.status = right_status;
		} else {
			g_shell_data.status = 1; 
		}

	} else if (node->type == LogicalAnd) {
		//dprintf(2, "LogicalAnd\n");
		execute_ast(node->left);
		
		int left_status = WEXITSTATUS(g_shell_data.status);
		// dprintf(2, "status %d\n", left_status);
		if (left_status == 0) {
			execute_ast(node->right);
		}
	} else if (node->type == LogicalOr) {
		//dprintf(2, "LogicalOr\n");

		execute_ast(node->left);
		
		int left_status = g_shell_data.status;
		if (left_status != 0) {
			execute_ast(node->right);
		}
	} else if (node->type == LessThanOperator) {
		//dprintf(2, "LessThanOperator\n");
		int fd = open(node->right->args[0], O_RDONLY);
		//dprintf(2, "fd = %d\n", fd);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd); 
		execute_ast(node->left);
	} else if (node->type == GreaterThanOperator) {
		//dprintf(2, "GreaterThanOperator\n");

		int fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd); 
		execute_ast(node->left); 
	} else if (node->type == DoubleLessThanOperator) {
		//dprintf(2, "DoubleLessThanOperator\n");

		
		int fd = open(node->right->args[0], O_RDONLY);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO); 
		close(fd); 
		execute_ast(node->left);
	} else if (node->type == DoubleGreaterThanOperator) {
		//dprintf(2, "DoubleGreaterThanOperator\n");

		
		int fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd); 
		execute_ast(node->left); 
	} else if (node->type == OpeningParenthesis) {
		
		execute_ast(node->left);
	}
	// g_shell_data.status = status;
}


void	execution(void)
{
	// printf("nbr cmd = %d\n", g_shell_data.nbr_cmd);
	// if (g_shell_data.nbr_cmd == 1)
	// {
	// 	if (check_if_builtin(g_shell_data.ast->args[0]))
	// 		execute_builtin(g_shell_data.ast->args);
	// 	else
	// 		execute_single_cmd();
	// }
	execute_ast(g_shell_data.ast); 
	
}
